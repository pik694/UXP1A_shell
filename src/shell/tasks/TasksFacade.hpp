//
// Created by Piotr Żelazko on 02.06.2018.
//

#ifndef UXP1A_SHELL_TASKSFACADE_HPP
#define UXP1A_SHELL_TASKSFACADE_HPP

namespace shell::tasks {
    class TasksFacade {
    public:


        //TODO: thread safe
        void buildAndAddTask();


        void close();


    };
}


#endif //UXP1A_SHELL_TASKSFACADE_HPP
