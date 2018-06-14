//
// Created by Piotr Żelazko on 02.06.2018.
//

#ifndef UXP1A_SHELL_TASKSFACTORY_HPP
#define UXP1A_SHELL_TASKSFACTORY_HPP

#include <memory>
#include <shell/tasks/domain/tasks/Task.hpp>
#include <shell/command_parser/structures/AbstractSyntaxTree.hpp>

namespace shell::tasks {
class TasksFactory : public shell::parser::structures::Visitor {
    public:
        std::unique_ptr<Task> build(std::unique_ptr<parser::structures::ast> ast);

    std::unique_ptr<Task> visit( parser::structures::Assignment &assignment ) override;
    std::unique_ptr<Task> visit( parser::structures::HereDocument &here_document ) override;
    std::unique_ptr<Task> visit( parser::structures::Pipeline &pipeline ) override;
    };
}


#endif //UXP1A_SHELL_TASKSFACTORY_HPP
