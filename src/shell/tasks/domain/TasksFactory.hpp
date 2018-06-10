//
// Created by Piotr Żelazko on 02.06.2018.
//

#ifndef UXP1A_SHELL_TASKSFACTORY_HPP
#define UXP1A_SHELL_TASKSFACTORY_HPP

#include <memory>
#include <shell/tasks/domain/tasks/Task.hpp>
#include <shell/command_parser/AbstractSyntaxTree.hpp>

namespace shell::tasks {
    class TasksFactory {
    public:

        std::unique_ptr<Task> build(std::unique_ptr<parser::ast> ast);
    };
}


#endif //UXP1A_SHELL_TASKSFACTORY_HPP
