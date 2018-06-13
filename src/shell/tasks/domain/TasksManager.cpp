//
// Created by Piotr Żelazko on 10.06.2018.
//

#include <iostream>
#include <csignal>
#include <unistd.h>
#include "TasksManager.hpp"

using namespace shell::tasks;

TasksManager *TasksManager::instance_ = nullptr;

void TasksManager::handleSigChld(int signal) {
    std::lock_guard guard(instance_->mutex_);
    instance_->childrenExited_ = true;
    instance_->conditionVariable_.notify_one();
}


TasksManager::TasksManager() :
        workerThread_(std::bind(&TasksManager::worker, this)),
        stdinCopy(dup(STDIN_FILENO)),
        stdoutCopy(dup(STDOUT_FILENO)),
        stderrCopy(dup(STDERR_FILENO)) {

    instance_ = this;

    std::signal(SIGCHLD, TasksManager::handleSigChld);

}

void TasksManager::close() {

    killChildren();

    {
        std::lock_guard guard(mutex_);
        shouldFinish_ = true;
    }
    conditionVariable_.notify_one();

    workerThread_.join();

}

void TasksManager::addTask(std::unique_ptr<Task> task) {

    if (shouldFinish_) return;

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

    while (!shouldFinish_) {

        std::unique_lock<std::mutex> lock(mutex_);
        conditionVariable_.wait(lock, [this]() {
            return childrenExited_ || shouldFinish_;
        });
        childrenExited_ = false;
        lock.unlock();


        pid_t child;
        //TODO: set ? variable
        while ((child = waitpid(0, nullptr, WNOHANG)) > 0) {
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

    pid_t child;
    while ((child = waitpid(0, nullptr, 0)) > 0) {
        std::lock_guard guard(runningChildrenMutex_);
        runningChildren_.erase(child);
    }


}

void TasksManager::recoverStreams() {

    dup2(stdinCopy, STDIN_FILENO);
    dup2(stdoutCopy, STDOUT_FILENO);
    dup2(stderrCopy, STDERR_FILENO);

}

