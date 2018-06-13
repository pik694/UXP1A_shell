//
// Created by Piotr Żelazko on 02.06.2018.
//

#ifndef UXP1A_SHELL_TASK_HPP
#define UXP1A_SHELL_TASK_HPP

#include <sys/types.h>
#include <boost/optional.hpp>

namespace shell::tasks {

    class Task {
    public:

        virtual boost::optional<pid_t> run() = 0;

        virtual bool isBackgroundTask(){return false;}

        virtual ~Task() = default;


    };
}


#endif //UXP1A_SHELL_TASK_HPP
