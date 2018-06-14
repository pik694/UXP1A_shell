//
// Created by Piotr Żelazko on 13.06.2018.
//


#include <shell/tasks/domain/TasksManager.hpp>
#include <iostream>
#include <fcntl.h>

namespace test::shell::tasks {
    using namespace ::shell::tasks;

    class TasksManagerTester {
    public:

        explicit TasksManagerTester(TasksManager const &manager) : manager_(manager) {}

        std::queue<pid_t> const &getLastExitedChildren() {
            return manager_.lastExitedChildren_;
        }

        TasksManager::running_children_t const &getRunningChildren() {
            return manager_.runningChildren_;
        }

    private:
        TasksManager const &manager_;
    };

    class MockTask : public Task {
    public:
        boost::optional<pid_t> run() override {
            return boost::none;
        }
    };

    class MockChildProcessTask : public Task {
    public:

        explicit MockChildProcessTask(pid_t pid = 1) : pid_(pid) {}


        boost::optional<pid_t> run() override {
            return pid_;
        }

    private:
        pid_t pid_;
    };

    class MockChildProcessRunningTask : public Task {
    public:

        explicit MockChildProcessRunningTask(uint8_t exitCode = 0) : exitCode_(exitCode) {}

        boost::optional<pid_t> run() override {
            pid_t child;
            if ((child = fork())) {
                return child;
            } else {
                exit(exitCode_);
            }
        }

    private:
        uint8_t exitCode_;
    };

    class MockReadTask : public Task {
    public:

        boost::optional<pid_t> run() override {

            int res = -1;

            std::cin >> res;

            return res;
        }

    };

    class MockWriteTask : public Task {
    public:

        MockWriteTask(const std::string &text) : text_(text) {}

        boost::optional<pid_t> run() override {

            std::cout << text_ << std::endl;

            return boost::none;
        }

    private:
        std::string text_;
    };

    class MockWriteProcessTask : public Task {
    public:

        MockWriteProcessTask(const std::string &text) : text_(text) {}

        boost::optional<pid_t> run() override {

            pid_t pid = fork();

            if (pid < 0)
                throw std::system_error(errno, std::system_category());


            if (pid == 0) {

                int outDesc = open("/tmp/uxp1a_shell/pipelines/pipe0", O_WRONLY | O_NONBLOCK);

                if (outDesc == -1)
                    throw std::system_error(errno, std::system_category());

                int descriptorCopy = dup(STDOUT_FILENO);
                dup2(outDesc, STDOUT_FILENO);

                std::cout << 10 << std::endl;

                fflush(stdout);

                dup2(descriptorCopy, STDOUT_FILENO);
                close(descriptorCopy);

                exit(0);

            }

            return pid;

        }

    private:
        std::string text_;
    };

}