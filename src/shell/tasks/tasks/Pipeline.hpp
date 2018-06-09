//
// Created by Piotr Żelazko on 02.06.2018.
//

#ifndef UXP1A_SHELL_PIPELINE_HPP
#define UXP1A_SHELL_PIPELINE_HPP

#include <memory>
#include <string>
#include "Task.hpp"

namespace shell::tasks{
    class Pipeline {

    private:
        const std::string name_;
        std::weak_ptr<Task> writer_;
        std::weak_ptr<Task> reader_;
    };
}


#endif //UXP1A_SHELL_PIPELINE_HPP
