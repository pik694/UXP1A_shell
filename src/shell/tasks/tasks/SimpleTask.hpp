//
// Created by Piotr Żelazko on 09.06.2018.
//

#ifndef UXP1A_SHELL_SIMPLETASK_HPP
#define UXP1A_SHELL_SIMPLETASK_HPP

#include <string>
#include <list>

#include "Task.hpp"

namespace shell::tasks {


    class SimpleTask : Task {


    private:
        std::list<const std::string> args_;
        const std::string programName_;
    };

}

#endif //UXP1A_SHELL_SIMPLETASK_HPP
