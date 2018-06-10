//
// Created by Piotr Żelazko on 10.06.2018.
//

#include "TasksFacade.hpp"

using namespace shell::tasks;

void TasksFacade::buildAndAddTask(std::unique_ptr<shell::parser::ast> ast) {

    auto task = factory_.build(std::move(ast));

    manager_.addTask(std::move(task));
}

void TasksFacade::close() {

    manager_.close();

}
