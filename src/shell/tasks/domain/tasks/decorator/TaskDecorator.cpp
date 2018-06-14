//
// Created by Piotr Żelazko on 09.06.2018.
//

#include "TaskDecorator.hpp"

using namespace shell::tasks::decorators;



boost::optional<pid_t> TaskDecorator::run() {
    return decoratedTask_->run();
}

bool TaskDecorator::isBackgroundTask() {
    return decoratedTask_->isBackgroundTask();
}

TaskDecorator::~TaskDecorator() {}





