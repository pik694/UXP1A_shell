//
// Created by Piotr Żelazko on 02.06.2018.
//

#ifndef UXP1A_SHELL_TASKSMANAGER_HPP
#define UXP1A_SHELL_TASKSMANAGER_HPP

#include <memory>
#include <shell/tasks/domain/tasks/Task.hpp>
#include <list>
#include <mutex>
#include <unordered_map>

namespace shell::tasks {
    //TODO: on the diagram it is called "task runner"
    class TasksManager {
    public:

        // TODO: should run in another thread

        void addTask(std::unique_ptr<Task> task);

        //TODO: blocking method that should wait until managers thread finishes
        //TODO: manager thread kills its children (running tasks) and waits until they finish
        void close();

    private:

        std::mutex mutex_;

        std::unordered_map<size_t, std::unique_ptr<Task>> runningTasks_;

    };
}


#endif //UXP1A_SHELL_TASKSMANAGER_HPP
