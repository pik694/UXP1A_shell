//
// Created by Piotr Żelazko on 10.06.2018.
//

#include <shell/command_parser/structures/Assignment.h>
#include <shell/command_parser/structures/Pipeline.h>
#include <shell/tasks/domain/tasks/AssignVariableTask.hpp>
#include <shell/tasks/domain/tasks/ChildProcess.hpp>
#include <shell/tasks/domain/tasks/PipelinedTasks.hpp>
#include <shell/tasks/domain/tasks/decorator/BackgroundTask.hpp>

#include "TasksFactory.hpp"

using namespace shell::tasks;


std::unique_ptr<Task> TasksFactory::build(std::unique_ptr<shell::parser::structures::ast> ast) {
    return ast->accept(*this);
}

std::unique_ptr<Task> TasksFactory::visit(shell::parser::structures::Assignment &assignment) {
    return std::unique_ptr<Task>(new AssignVariableTask(assignment.getVariable(), assignment.getValue()));
}

std::unique_ptr<Task> TasksFactory::visit(shell::parser::structures::HereDocument &here_document) {
    //TODO
    throw std::runtime_error("Not implemented yet");
}

std::unique_ptr<Task> TasksFactory::visit(shell::parser::structures::Pipeline &pipeline) {
    auto &commandLists = pipeline.getCommandsList();

    if (commandLists.size() > 1) {
        std::list<std::unique_ptr<Task>> list;

        for (auto &commandList : commandLists)
            for (auto &command : commandList->getCommands())
                list.emplace_back(buildTaskFromCommand(*command));


        return std::unique_ptr<Task>(new PipelinedTasks(manager_, std::move(list)));


    } else
        for (auto &commandList : commandLists)
            for (auto &command : commandList->getCommands()) {
                return buildTaskFromCommand(*command);
            }

}

std::unique_ptr<Task> TasksFactory::buildTaskFromCommand(shell::parser::structures::Command &command) {

    std::list<std::string> args(command.getArguments().begin(), command.getArguments().end());

    auto task = std::unique_ptr<Task>(new ChildProcess(command.getWord(), args));


    if (command.getIsBackground()){
        task = std::unique_ptr<Task>(new decorators::BackgroundTask(std::move(task)));
    }

//    for (auto& redirection : command.getRedirections()){
//        if (dynamic_cast<shell::parser::structures::Redirection>)
//    }

    return std::move(task);
}

TasksFactory::TasksFactory(TasksManager &manager_) : manager_(manager_) {}


