//
// Created by Piotr Żelazko on 13.06.2018.
//

#include <fcntl.h>
#include <string>
#include <system_error>
#include "StandardOutputRedirector.hpp"

using namespace shell::tasks::decorators;


StandardOutputRedirector::StandardOutputRedirector(std::unique_ptr<shell::tasks::Task> decoratedTask, int descriptor)
        : StreamRedirector(std::move(decoratedTask), descriptor) {

}

StandardOutputRedirector::StandardOutputRedirector(std::unique_ptr<shell::tasks::Task> decoratedTask,
                                                   const std::string &filename, bool append) :
        StreamRedirector(std::move(decoratedTask), filename,
                         append ? (O_WRONLY | O_CREAT | O_APPEND) : (O_WRONLY | O_CREAT)) {

}

int StandardOutputRedirector::getStream() {
    return STDOUT_FILENO;
}