//
// Created by Piotr Żelazko on 13.06.2018.
//

#ifndef UXP1A_SHELL_STANDARDERRORREDIRECTOR_HPP
#define UXP1A_SHELL_STANDARDERRORREDIRECTOR_HPP

#include "TaskDecorator.hpp"
#include "StandardOutputRedirector.hpp"

namespace shell::tasks::decorators {

    class StandardErrorRedirector : public StandardOutputRedirector{
    public:
        StandardErrorRedirector(std::unique_ptr<Task> decoratedTask, int descriptor);

        StandardErrorRedirector(std::unique_ptr<Task> decoratedTask, const std::string& filename, bool append = true);

    private:
        int getStream() override;

    };
}


#endif //UXP1A_SHELL_STANDARDERRORREDIRECTOR_HPP
