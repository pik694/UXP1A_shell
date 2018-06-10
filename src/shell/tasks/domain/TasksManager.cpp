//
// Created by Piotr Żelazko on 10.06.2018.
//

#include <iostream>
#include <csignal>
#include "TasksManager.hpp"

using namespace shell::tasks;

TasksManager::TasksManager() :
        workerThread_(std::bind(&TasksManager::worker, this)) {}

void TasksManager::close() {

    killChildren();

    shouldFinish_ = true;
    childrenExitedCV_.notify_one();

    workerThread_.join();


}

TasksManager::~TasksManager() {
    workerThread_.join();
}

void TasksManager::addTask(std::unique_ptr<Task> task) {

    if (shouldFinish_) return;
    task->run(*this);

}

void TasksManager::waitForChild(pid_t child) {

    std::unique_lock<std::mutex> lock(lastExitedMutex_);
    lastExitedCV_.wait(lock, [this]() {
        while (!lastExitedChildren_.empty()) {
            if (lastExitedChildren_.front() == child) return true;
            lastExitedChildren_.pop();
        }
        return false;
    });

    lock.unlock();
}

void TasksManager::addBackgroundChild(pid_t child) {

    std::lock_guard guard(runningChildrenMutex_);
    runningChildren_.insert(child);

}

void TasksManager::killChildren() {

    std::lock_guard guard(runningChildrenMutex_);

    for (auto child : runningChildren_)
        kill(child, SIGKILL);
}


void TasksManager::worker() {

    std::signal(SIGCHLD, [this](int) {
        std::lock_guard(childrenExitedMutex_);
        childrenExited = true;
        childrenExitedCV_.notify_one();
    });

    while (!shouldFinish_) {
        std::unique_lock<std::mutex> lock(childrenExitedMutex_);
        childrenExitedCV_.wait(lock, [this]() {
            return childrenExited || shouldFinish_;
        });
        childrenExited = false;
        lock.unlock();

        pid_t child;
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

    while (!runningChildren_.empty()) {
        std::unique_lock<std::mutex> lock(childrenExitedMutex_);
        childrenExitedCV_.wait(lock, [this]() {
            return childrenExited;
        });
        childrenExited = false;
        lock.unlock();

        pid_t child;
        while ((child = waitpid(0, nullptr, WNOHANG)) > 0) {
            std::lock_guard guard(runningChildrenMutex_);
            runningChildren_.erase(child);
        }
        if (child < 0) break;
    }


}



