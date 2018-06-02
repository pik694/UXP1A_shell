//
// Created by Piotr Żelazko on 02.06.2018.
//

#ifndef UXP1A_SHELL_TASKSMANAGER_HPP
#define UXP1A_SHELL_TASKSMANAGER_HPP

namespace shell::tasks {
    //TODO: on the diagram it is called "task runner"
    class TasksManager {
    public:

        // TODO: should run in another thread

        void addTask();

        //TODO: blocking method that should wait until managers thread finishes
        //TODO: manager thread kills its children (running tasks) and waits until they finish
        void close();

    };
}


#endif //UXP1A_SHELL_TASKSMANAGER_HPP
