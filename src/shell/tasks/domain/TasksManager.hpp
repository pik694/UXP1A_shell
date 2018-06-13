//
// Created by Piotr Żelazko on 02.06.2018.
//

#ifndef UXP1A_SHELL_TASKSMANAGER_HPP
#define UXP1A_SHELL_TASKSMANAGER_HPP

#include <memory>
#include <shell/tasks/domain/tasks/Task.hpp>
#include <list>
#include <queue>
#include <thread>
#include <unordered_map>

namespace test::shell::tasks{
    class TasksManagerTester;
}

namespace shell::tasks {
    class TasksManager {
    public:

        using running_children_t = std::unordered_map<pid_t, std::unique_ptr<Task>>;

        TasksManager();

        void addTask(std::unique_ptr<Task> task);

        void close();

        virtual ~TasksManager() = default;

    private:

        void worker();

        void killChildren();

        void waitForChild(pid_t pid);

        bool waitForShouldFinish();

        void pollExitedChildren(int flags = 0);

        std::thread workerThread_;

        std::mutex shouldFinishMutex_;
        std::condition_variable shouldFinishCV_;
        bool shouldFinish_ = false;

        std::mutex runningChildrenMutex_;
        running_children_t runningChildren_;

        std::mutex lastExitedMutex_;
        std::condition_variable lastExitedCV_;
        std::queue<pid_t> lastExitedChildren_;

        void recoverStreams();

        int stdoutCopy;
        int stdinCopy;
        int stderrCopy;

        friend class test::shell::tasks::TasksManagerTester;
    };

}


#endif //UXP1A_SHELL_TASKSMANAGER_HPP
