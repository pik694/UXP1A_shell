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
#include <set>

namespace shell::tasks {
    //TODO: on the diagram it is called "task runner"
    class TasksManager {
    public:

        TasksManager();

        // TODO: should run in another thread

        void addTask(std::unique_ptr<Task> task);

        void waitForChild(pid_t child);

        void addBackgroundChild(pid_t child);

        //TODO: blocking method that should wait until managers thread finishes
        //TODO: manager thread kills its children (running tasks) and waits until they finish
        void close();

        virtual ~TasksManager();

    private:

        void worker();

        void killChildren();


        std::thread workerThread_;

        std::atomic<bool> shouldFinish_ = false;

        std::mutex childrenExitedMutex_;
        std::condition_variable childrenExitedCV_;
        bool childrenExited = false;

        std::mutex runningChildrenMutex_;
        std::condition_variable runningChildrenCV_;
        std::set<pid_t> runningChildren_;

        std::mutex lastExitedMutex_;
        std::condition_variable lastExitedCV_;
        std::queue<pid_t> lastExitedChildren_;

    };
}


#endif //UXP1A_SHELL_TASKSMANAGER_HPP
