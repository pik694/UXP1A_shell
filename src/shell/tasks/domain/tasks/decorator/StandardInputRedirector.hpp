//
// Created by Piotr Żelazko on 13.06.2018.
//

#ifndef UXP1A_SHELL_STANDARDINPUTREDIRECTOR_HPP
#define UXP1A_SHELL_STANDARDINPUTREDIRECTOR_HPP


#include "StreamRedirector.hpp"

namespace shell::tasks::decorators {

    class StandardInputRedirector : public StreamRedirector {
    public:
        StandardInputRedirector(std::unique_ptr<Task> decoratedTask, int descriptor);
        StandardInputRedirector(std::unique_ptr<Task> decoratedTask, const std::string& filename);

    private:

        int getStream() override;
    };

}


#endif //UXP1A_SHELL_STANDARDINPUTREDIRECTOR_HPP
