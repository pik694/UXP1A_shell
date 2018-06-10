//
// Created by Piotr Żelazko on 10.06.2018.
//


#include "TasksFactory.hpp"

using namespace shell::tasks;


std::unique_ptr<Task> TasksFactory::build(std::unique_ptr<shell::parser::ast> ast) {
    //TODO
    throw std::runtime_error("Not implemented yet");
}
