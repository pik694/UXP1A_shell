//
// Created by Piotr Żelazko on 13.06.2018.
//


#include <shell/tasks/domain/TasksManager.hpp>

namespace test::shell::tasks {
    using namespace ::shell::tasks;

    class TasksManagerTester {
    public:

        TasksManagerTester(TasksManager const &manager) : manager_(manager) {}

        std::queue<pid_t> const &getLastExitedChildren() {
            return manager_.lastExitedChildren_;
        }

        bool getChildrenExited() {
            return manager_.childrenExited_;
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
        boost::optional <pid_t> run() override {
            return 1;
        }
    };

    class MockChildProcessRunningTask : public Task {
    public:
        boost::optional <pid_t> run() override {
            pid_t child;
            if ((child = fork())) {
                return child;
            } else {
                exit(0);
            }
        }
    };

}