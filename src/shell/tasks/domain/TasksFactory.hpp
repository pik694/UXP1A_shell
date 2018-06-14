//
// Created by Piotr Żelazko on 02.06.2018.
//

#ifndef UXP1A_SHELL_TASKSFACTORY_HPP
#define UXP1A_SHELL_TASKSFACTORY_HPP

#include <memory>
#include <shell/tasks/domain/tasks/Task.hpp>
#include <shell/command_parser/structures/AbstractSyntaxTree.hpp>
#include "TasksManager.hpp"

namespace shell::tasks {
    class TasksFactory : public shell::parser::structures::Visitor {
    public:
        TasksFactory(TasksManager &manager_);

        std::unique_ptr<Task> build(std::unique_ptr<parser::structures::ast> ast);

        std::unique_ptr<Task> visit(parser::structures::Assignment &assignment) override;

        std::unique_ptr<Task> visit(parser::structures::HereDocument &here_document) override;

        std::unique_ptr<Task> visit(parser::structures::Pipeline &pipeline) override;

    private:
        TasksManager& manager_;

        std::unique_ptr<Task> buildTaskFromCommand(shell::parser::structures::Command& command);
    };
}


#endif //UXP1A_SHELL_TASKSFACTORY_HPP
