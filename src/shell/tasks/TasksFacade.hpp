//
// Created by Piotr Żelazko on 02.06.2018.
//

#ifndef UXP1A_SHELL_TASKSFACADE_HPP
#define UXP1A_SHELL_TASKSFACADE_HPP

#include <memory>
#include <shell/command_parser/AbstractSyntaxTree.hpp>
#include <shell/tasks/domain/TasksFactory.hpp>
#include <shell/tasks/domain/TasksManager.hpp>

namespace shell::tasks {
    class TasksFacade {
    public:

        void buildAndAddTask(std::unique_ptr<shell::parser::ast> ast);

        void close();

    private:
        tasks::TasksManager manager_;
        tasks::TasksFactory factory_;

    };
}


#endif //UXP1A_SHELL_TASKSFACADE_HPP
