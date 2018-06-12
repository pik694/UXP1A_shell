//
// Created by Piotr Żelazko on 02.06.2018.
//

#ifndef UXP1A_SHELL_USERINTERFACE_HPP
#define UXP1A_SHELL_USERINTERFACE_HPP


#include <string>
#include <boost/optional.hpp>
#include <iostream>

namespace shell::ui {
    class UserInterface {
    public:

        boost::optional<std::string> getNextCommand()
        {
            std::string input;
            boost::optional<std::string> command;
            std::getline(std::cin, input);
            command.emplace(input);
            return command;
        }

        void printError(const std::string&);
        void printLog(const std::string&);


    };
}


#endif //UXP1A_SHELL_USERINTERFACE_HPP
