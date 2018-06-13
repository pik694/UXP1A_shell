//
// Created by Piotr Żelazko on 09.06.2018.
//

#include "AssignVariableTask.hpp"

using namespace shell::tasks;

AssignVariableTask::AssignVariableTask(std::string variable, std::string value)
        : variable_(std::move(variable)), value_(std::move(value)) {}

boost::optional<pid_t> AssignVariableTask::run() {

    //TODO: assign variable

    return boost::none;
}
