//
// Created by Piotr Żelazko on 09.06.2018.
//

#ifndef UXP1A_SHELL_SIMPLETASK_HPP
#define UXP1A_SHELL_SIMPLETASK_HPP

#include <string>
#include <list>

#include "Task.hpp"

namespace shell::tasks {

    class ChildProcess : public Task {
    public:

        ChildProcess(std::string programName_, std::list<const std::string> args_);

        boost::optional<pid_t> run() override;

    private:

        char *const *getArgs();

        const std::string programName_;
        std::list<const std::string> args_;
    };

}

#endif //UXP1A_SHELL_SIMPLETASK_HPP
