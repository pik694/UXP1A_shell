//
// Created by Piotr Żelazko on 10.06.2018.
//

#include <shell/command_parser/structures/Assignment.h>
#include <shell/tasks/domain/tasks/AssignVariableTask.hpp>

#include "TasksFactory.hpp"

using namespace shell::tasks;


std::unique_ptr<Task> TasksFactory::build(std::unique_ptr<shell::parser::structures::ast> ast)
{
    return ast->accept( *this );
}

std::unique_ptr<Task> TasksFactory::visit( shell::parser::structures::Assignment &assignment )
{
    return std::unique_ptr<Task> (new AssignVariableTask(assignment.getVariable(), assignment.getValue()));
}

std::unique_ptr<Task> TasksFactory::visit( shell::parser::structures::HereDocument &here_document )
{
    //TODO
    throw std::runtime_error("Not implemented yet");
}

std::unique_ptr<Task> TasksFactory::visit( shell::parser::structures::Pipeline &pipeline )
{
    //TODO
    throw std::runtime_error("Not implemented yet");
}
