//
// Created by Piotr Żelazko on 09.06.2018.
//

#ifndef UXP1A_SHELL_TASKDECORATOR_HPP
#define UXP1A_SHELL_TASKDECORATOR_HPP

#include <memory>
#include <shell/tasks/domain/tasks/Task.hpp>

namespace shell::tasks::decorators{
    class TaskDecorator : Task {

        pid_t run(TasksManager& manager) override {
            decoratedTask_->run(manager);
        }

    private:
        std::unique_ptr<Task> decoratedTask_;
    };
}

#endif //UXP1A_SHELL_TASKDECORATOR_HPP
