//
// Created by Piotr Żelazko on 02.06.2018.
//

#ifndef UXP1A_SHELL_CONTROLLER_HPP
#define UXP1A_SHELL_CONTROLLER_HPP

#include <iostream>
#include <csignal>
#include <zconf.h>

using namespace shell::model;
using namespace shell::parser;
using namespace shell::tasks;


namespace shell::ui {
    class Controller {
    public:

        static Controller &getInstance()
        {
            static Controller instance;
            return instance;
        }

        void start()
        {
            std::unique_ptr<TasksFacade> tasksFacade(new TasksFacade);
            initializeSignals();

            while (true) {
                showHeader();
                std::string command = userInterface->getNextCommand().get();
                tasksFacade->buildAndAddTask(parser->buildTree(command));
            }
        }

        void showHeader()
        {
            std::cout << "\nUXP1A@" << getHostName() << ":" << getCurrentDirectory() << "$ ";
        }

        const std::string getHostName()
        {
            char hostName[HOST_NAME_SIZE];
            if (gethostname(hostName, HOST_NAME_SIZE - 1) != -1) {
                hostName[HOST_NAME_SIZE - 1] = 0;
                return (const std::string) hostName;
            }

            return UNKNOWN_HOST_NAME;
        }

        const std::string getCurrentDirectory()
        {
            char currentDir[CURRENT_DIR_SIZE];
            if (getcwd(currentDir, CURRENT_DIR_SIZE - 1) != NULL) {
                currentDir[CURRENT_DIR_SIZE - 1] = 0;
                return (const std::string) currentDir;
            }

            return UNKNOWN_CURRENT_DIR;
        }

        std::unique_ptr<Variable> getVariable(const std::string &variable)
        {
            return modelFacade->getVariable(variable);
        }

        void initializeSignals()
        {
            signal(SIGINT, signalHandler);
            signal(SIGTSTP, signalHandler);
            signal(SIGTTIN, SIG_IGN);
            signal(SIGTTOU, SIG_IGN);
        }

        static inline void signalHandler(int sigType)
        {
            if (sigType == SIGINT) {

            } else if (sigType == SIGTSTP) {
                exit(0);
            }
        }

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
