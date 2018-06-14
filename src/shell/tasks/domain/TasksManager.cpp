//
// Created by Piotr Żelazko on 10.06.2018.
//

#include <iostream>
#include <csignal>
#include <unistd.h>
#include <sys/wait.h>
#include <shell/model/ModelFacade.hpp>
#include <shell/ui/Controller.hpp>
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
        std::lock_guard guard(shouldFinishMutex_);
        if (shouldFinish_) return;
    }


    auto pid = task->run();

    if (pid) {
        if (task->isBackgroundTask())
            runningChildren_.insert({*pid, std::move(task)});
        else
            waitForForegroundChild(*pid);
    }

    recoverStreams();
}


void TasksManager::waitForForegroundChild(pid_t child) {

    std::unique_lock<std::mutex> lock(lastExitedMutex_);
    lastExitedCV_.wait(lock, [=]() {

        while (!lastExitedChildren_.empty()) {
            if (lastExitedChildren_.front() == child) return true;
            lastExitedChildren_.pop();
        }
        return false;
    });

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

    bool shouldFinish = false;

    try {

        std::unique_lock<std::mutex> lock(shouldFinishMutex_);

        shouldFinish = shouldFinishCV_.wait_for(lock, 500ms, [this]() {
            return shouldFinish_;
        });
    }
    catch (std::exception& e){
        std::cerr << e.what() << std::endl;
    }

    return shouldFinish;

}

void TasksManager::pollExitedChildren(int flags) {



    boost::optional<std::pair<pid_t, int>> result;
    while ((result = waitForChild(flags))) {
        {
            std::lock_guard guard(lastExitedMutex_);
            lastExitedChildren_.push(result->first);
            lastExitedCV_.notify_one();
        }
        {
            std::lock_guard guard(runningChildrenMutex_);
            runningChildren_.erase(result->first);
        }
        shell::ui::Controller::getInstance().setVariable("?", std::to_string(result->second >> 8));
    }
}

void TasksManager::recoverStreams() {

    dup2(stdinCopy, STDIN_FILENO);
    dup2(stdoutCopy, STDOUT_FILENO);
    dup2(stderrCopy, STDERR_FILENO);

}

boost::optional<std::pair<pid_t, int>> TasksManager::waitForChild(int flags) {

    pid_t child;
    int status;

    while ((child = waitpid(-1, &status, flags)) < 0)
        if (errno == ECHILD) return boost::none;

    return std::make_pair(child, status);


}
