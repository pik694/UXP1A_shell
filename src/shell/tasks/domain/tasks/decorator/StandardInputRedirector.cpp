//
// Created by Piotr Żelazko on 13.06.2018.
//

#include <fcntl.h>
#include "StandardInputRedirector.hpp"

using namespace shell::tasks::decorators;

StandardInputRedirector::StandardInputRedirector(std::unique_ptr<shell::tasks::Task> decoratedTask, int descriptor)
        : StreamRedirector(std::move(decoratedTask), descriptor) {

}

StandardInputRedirector::StandardInputRedirector(std::unique_ptr<shell::tasks::Task> decoratedTask,
                                                 const std::string &filename):
StreamRedirector(std::move(decoratedTask), filename, (O_RDONLY))

{

}

int StandardInputRedirector::getStream() {
    return STDIN_FILENO;
}

