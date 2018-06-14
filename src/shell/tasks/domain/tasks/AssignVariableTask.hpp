//
// Created by Piotr Żelazko on 09.06.2018.
//

#ifndef UXP1A_SHELL_ASSIGNVARIABLETASK_HPP
#define UXP1A_SHELL_ASSIGNVARIABLETASK_HPP

#include <string>
#include "Task.hpp"

namespace shell::tasks {
    class AssignVariableTask : public Task {
    public:
        AssignVariableTask(std::string variable_, std::string value_);

        boost::optional<pid_t> run() override;

    private:
        const std::string variable_;
        const std::string value_;
    };
}

#endif //UXP1A_SHELL_ASSIGNVARIABLETASK_HPP
