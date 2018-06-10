//
// Created by Piotr Żelazko on 02.06.2018.
//

#ifndef UXP1A_SHELL_TASK_HPP
#define UXP1A_SHELL_TASK_HPP

#include <shell/tasks/domain/TasksManager.hpp>

namespace shell::tasks {

    class Task {
    public:

        virtual pid_t run(TasksManager& manager) = 0;

        virtual ~Task() = default;
    };
}


#endif //UXP1A_SHELL_TASK_HPP
