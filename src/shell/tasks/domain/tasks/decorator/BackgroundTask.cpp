//
// Created by Piotr Żelazko on 09.06.2018.
//

#include "BackgroundTask.hpp"

shell::tasks::decorators::BackgroundTask::BackgroundTask(std::unique_ptr<shell::tasks::Task> decoratedTask)
        : TaskDecorator(std::move(decoratedTask)) {}

bool shell::tasks::decorators::BackgroundTask::isBackgroundTask() {
    return true;
}
