//
// Created by Piotr Żelazko on 13.06.2018.
//


#include <shell/tasks/domain/TasksManager.hpp>

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
        boost::optional <pid_t> run() override {
            return boost::none;
        }
    };

    class MockChildProcessTask : public Task {
    public:

        explicit MockChildProcessTask(pid_t pid = 1) : pid_(pid) {}


        boost::optional <pid_t> run() override {
            return pid_;
        }

    private:
        pid_t pid_;
    };

    class MockChildProcessRunningTask : public Task {
    public:

        explicit MockChildProcessRunningTask(uint8_t exitCode = 0) : exitCode_(exitCode) {}

        boost::optional <pid_t> run() override {
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

}