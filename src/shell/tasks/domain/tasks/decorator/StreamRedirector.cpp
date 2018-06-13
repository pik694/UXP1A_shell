//
// Created by Piotr Żelazko on 13.06.2018.
//

#include <fcntl.h>
#include <iostream>
#include "StreamRedirector.hpp"


using namespace shell::tasks::decorators;

StreamRedirector::StreamRedirector(std::unique_ptr<shell::tasks::Task> decoratedTask, int descriptor) :
        TaskDecorator(std::move(decoratedTask)),
        descriptor_(descriptor) {

}

StreamRedirector::StreamRedirector(std::unique_ptr<shell::tasks::Task> decoratedTask, const std::string &filename,
                                   int flags) : TaskDecorator(std::move(decoratedTask))
{
    descriptor_ = open(filename.c_str(), flags);

    if (descriptor_ < 0)
        throw std::system_error(errno, std::system_category());
}

boost::optional<pid_t> StreamRedirector::run() {

    int descriptorCopy = dup(getStream());
    dup2(descriptor_, getStream());

    auto result = TaskDecorator::run();

    dup2(descriptorCopy, getStream());
    close(descriptorCopy);

    return result;

}


StreamRedirector::~StreamRedirector() {
    close(descriptor_);
}
