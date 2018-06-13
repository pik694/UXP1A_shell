//
// Created by Michal Smola on 6/13/18.
//

#include "UserInterface.hpp"

using namespace shell::ui;

boost::optional<std::string> UserInterface::getNextCommand()
{
    std::string input;
    boost::optional<std::string> command;
    std::getline(std::cin, input);
    command.emplace(input);
    return command;
}

void UserInterface::printError(const std::string& message)
{
    std::cerr << "Error:" << message << std::endl;
}