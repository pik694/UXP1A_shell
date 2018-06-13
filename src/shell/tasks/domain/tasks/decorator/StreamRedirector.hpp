//
// Created by Piotr Żelazko on 13.06.2018.
//

#ifndef UXP1A_SHELL_STREAMREDIRECTOR_HPP
#define UXP1A_SHELL_STREAMREDIRECTOR_HPP

#include "TaskDecorator.hpp"

namespace shell::tasks::decorators {
    class StreamRedirector : public TaskDecorator {
    public:

        StreamRedirector(std::unique_ptr<Task> decoratedTask, int descriptor);

        StreamRedirector(std::unique_ptr<Task> decoratedTask,const std::string& filename, int flags);

        ~StreamRedirector() override;

        boost::optional<pid_t> run() override;

    private:

        virtual int getStream() = 0;
        int descriptor_;

    };
}


#endif //UXP1A_SHELL_STREAMREDIRECTOR_HPP
