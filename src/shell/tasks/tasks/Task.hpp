//
// Created by Piotr Żelazko on 02.06.2018.
//

#ifndef UXP1A_SHELL_TASK_HPP
#define UXP1A_SHELL_TASK_HPP

namespace shell::tasks {

    class Task {
    public:

        virtual void run() = 0;

        virtual ~Task() = default;
    };
}


#endif //UXP1A_SHELL_TASK_HPP
