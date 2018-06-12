//
// Created by Piotr Żelazko on 02.06.2018.
//

#ifndef UXP1A_SHELL_TASKSFACADE_HPP
#define UXP1A_SHELL_TASKSFACADE_HPP

#include <memory>
#include <shell/command_parser/structures/AbstractSyntaxTree.hpp>

namespace shell::tasks {
    class TasksFacade {
    public:

        //TODO: thread safe
        void buildAndAddTask(std::unique_ptr<shell::parser::ast> ast);


        void close();

    };
}


#endif //UXP1A_SHELL_TASKSFACADE_HPP
