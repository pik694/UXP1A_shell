//
// Created by Piotr Żelazko on 09.06.2018.
//

#include <system_error>
#include "ChildProcess.hpp"

shell::tasks::ChildProcess::ChildProcess(std::string programName, std::list<std::string> args)
        : programName_(std::move(programName)), args_(std::move(args)) {}

boost::optional<pid_t> shell::tasks::ChildProcess::run() {

    pid_t pid = fork();

    if (pid < 0)
        throw std::system_error(errno, std::system_category());


    if (pid == 0) {

        execvp(programName_.c_str(), getArgs());

        throw std::system_error(errno, std::system_category());

    }

    return pid;
}

char *const *shell::tasks::ChildProcess::getArgs() {

    char **args = new char *[args_.size() + 2];
    size_t i = 0;

    args[i++] = const_cast<char *>(programName_.c_str());

    for (auto &arg : args_)
        args[i++] = const_cast<char *>(arg.c_str());

    args[i] = nullptr;


    return args;
}

