//
// Created by Piotr Żelazko on 09.06.2018.
//

#ifndef UXP1A_SHELL_TASKDECORATOR_HPP
#define UXP1A_SHELL_TASKDECORATOR_HPP

#include <memory>
#include <shell/tasks/domain/tasks/Task.hpp>

namespace shell::tasks::decorators {
    class TaskDecorator : public Task {

    public:
        explicit TaskDecorator(std::unique_ptr<Task> decoratedTask) : decoratedTask_(std::move(decoratedTask)) {}

        boost::optional<pid_t> run() override;

        ~TaskDecorator() override = 0;

    private:
        const std::unique_ptr<Task> decoratedTask_;
    };
}

#endif //UXP1A_SHELL_TASKDECORATOR_HPP
