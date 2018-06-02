//
// Created by Piotr Żelazko on 02.06.2018.
//

#ifndef UXP1A_SHELL_CONTROLLER_HPP
#define UXP1A_SHELL_CONTROLLER_HPP

namespace shell::ui {
    class Controller {
    public:

        //TODO: Main loop goes here
        void operator();

        void getVariable();

        //TODO: should implement catching SIGKILL event


        //TODO: should proxy all inter-modules communication

        //TODO: the only class that can be written as a singleton (not necessarily has to)

    };
}


#endif //UXP1A_SHELL_CONTROLLER_HPP
