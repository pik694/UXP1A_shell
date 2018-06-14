//
// Created by Piotr Żelazko on 09.06.2018.
//

#ifndef UXP1A_SHELL_BACKGROUNDTASK_HPP
#define UXP1A_SHELL_BACKGROUNDTASK_HPP

#include "TaskDecorator.hpp"

namespace shell::tasks::decorators {

    class BackgroundTask : public TaskDecorator {
    public:
        explicit BackgroundTask(std::unique_ptr<Task> decoratedTask);

        bool isBackgroundTask() override;
    };

}

#endif //UXP1A_SHELL_BACKGROUNDTASK_HPP
