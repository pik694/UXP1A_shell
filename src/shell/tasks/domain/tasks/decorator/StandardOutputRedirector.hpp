//
// Created by Piotr Żelazko on 13.06.2018.
//

#ifndef UXP1A_SHELL_STANDARDOUTPUTREDIRECTOR_HPP
#define UXP1A_SHELL_STANDARDOUTPUTREDIRECTOR_HPP

#include "StreamRedirector.hpp"

namespace shell::tasks::decorators {
    class StandardOutputRedirector : public StreamRedirector {
    public:

        StandardOutputRedirector(std::unique_ptr<Task> decoratedTask, int descriptor);
        StandardOutputRedirector(std::unique_ptr<Task> decoratedTask, const std::string& filename, bool append = false);


    private:
        int getStream() override;

    };
}

#endif //UXP1A_SHELL_STANDARDOUTPUTREDIRECTOR_HPP
