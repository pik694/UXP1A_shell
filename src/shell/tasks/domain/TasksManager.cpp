//
// Created by Piotr Żelazko on 10.06.2018.
//

#include <iostream>
#include <csignal>
#include <unistd.h>
#include "TasksManager.hpp"

using namespace shell::tasks;

TasksManager::TasksManager() :
        workerThread_(std::bind(&TasksManager::worker, this)),
        stdinCopy(dup(STDIN_FILENO)),
        stdoutCopy(dup(STDOUT_FILENO)),
        stderrCopy(dup(STDERR_FILENO)) {


}

void TasksManager::close() {

    killChildren();

    {
        std::lock_guard guard(shouldFinishMutex_);
        shouldFinish_ = true;
    }
    shouldFinishCV_.notify_one();

    workerThread_.join();

}

void TasksManager::addTask(std::unique_ptr<Task> task) {

    {
        std::lock_guard guard (shouldFinishMutex_);
        if (shouldFinish_) return;
    }


    auto pid = task->run();

    if (pid) {
        if (task->isBackgroundTask())
            runningChildren_.insert({*pid, std::move(task)});
        else
            waitForChild(*pid);
    }

    recoverStreams();
}


void TasksManager::waitForChild(pid_t child) {

    std::unique_lock<std::mutex> lock(lastExitedMutex_);
    lastExitedCV_.wait(lock, [=]() {
        while (!lastExitedChildren_.empty()) {
            if (lastExitedChildren_.front() == child) return true;
            lastExitedChildren_.pop();
        }
        return false;
    });

    lock.unlock();
}

void TasksManager::killChildren() {

    std::lock_guard guard(runningChildrenMutex_);
    for (auto &child : runningChildren_)
        kill(child.first, SIGKILL);
}


void TasksManager::worker() {

    while (!waitForShouldFinish())
        pollExitedChildren(WNOHANG);

    pollExitedChildren();

}

bool TasksManager::waitForShouldFinish() {

    using namespace std::chrono_literals;

    std::unique_lock<std::mutex> lock(shouldFinishMutex_);

    bool shouldFinish =  shouldFinishCV_.wait_for(lock, 500ms, [this]() {
        return shouldFinish_;
    });

    lock.unlock();

    return shouldFinish;

}

void TasksManager::pollExitedChildren(int flags) {

    pid_t child;
    int status;
    //TODO: set ? variable
    while ((child = waitpid(0, &status, flags)) > 0) {
        {
            std::lock_guard guard(lastExitedMutex_);
            lastExitedChildren_.push(child);
            lastExitedCV_.notify_one();
        }
        {
            std::lock_guard guard(runningChildrenMutex_);
            runningChildren_.erase(child);
        }
    }
}

void TasksManager::recoverStreams() {

    dup2(stdinCopy, STDIN_FILENO);
    dup2(stdoutCopy, STDOUT_FILENO);
    dup2(stderrCopy, STDERR_FILENO);

}

