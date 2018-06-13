//
// Created by Piotr Żelazko on 13.06.2018.
//


#include "StandardErrorRedirector.hpp"


using namespace shell::tasks::decorators;

StandardErrorRedirector::StandardErrorRedirector(std::unique_ptr<shell::tasks::Task> decoratedTask, int descriptor)
        : StandardOutputRedirector(std::move(decoratedTask), descriptor) {

}

StandardErrorRedirector::StandardErrorRedirector(std::unique_ptr<shell::tasks::Task> decoratedTask,
                                                 const std::string &filename, bool append) : StandardOutputRedirector(
        std::move(decoratedTask), filename, append) {

}

int StandardErrorRedirector::getStream() {
    return STDERR_FILENO;
}
