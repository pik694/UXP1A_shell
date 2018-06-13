//
// Created by Piotr Żelazko on 02.06.2018.
//

#ifndef UXP1A_SHELL_CONTROLLER_HPP
#define UXP1A_SHELL_CONTROLLER_HPP

#include <iostream>
#include <csignal>
#include <zconf.h>
#include <memory>
#include <atomic>
#include <shell/tasks/TasksFacade.hpp>
#include <shell/model/ModelFacade.hpp>
#include <shell/command_parser/Parser.hpp>
#include "UserInterface.hpp"

std::atomic<bool> shouldClose(false);

namespace shell::ui {
    class Controller {
    public:

        static Controller &getInstance()
        {
            static Controller instance;
            return instance;
        }

        void start();

        void showHeader();

        const std::string getHostName();

        const std::string getCurrentDirectory();

        std::unique_ptr<Variable> getVariable(const std::string &variable) const;

        void setVariable(const std::string &name, const std::string &value);

        void exportVariable(const std::string &name);

        void initializeSignals() const;

        static void signalHandler(int sigType);

        Controller(Controller const &) = delete;

        void operator=(Controller const &)   = delete;

    private:
        Controller()
        {
            setsid();
        }

        static Controller *instance;

        std::unique_ptr<Parser> parser;
        std::unique_ptr<UserInterface> userInterface;
        std::unique_ptr<ModelFacade> modelFacade;

        static const int HOST_NAME_SIZE = 64;
        static const int CURRENT_DIR_SIZE = 256;
        const std::string UNKNOWN_HOST_NAME = "unknownHostName";
        const std::string UNKNOWN_CURRENT_DIR = "unknownCurrentDirectory";
    };
}


#endif //UXP1A_SHELL_CONTROLLER_HPP
