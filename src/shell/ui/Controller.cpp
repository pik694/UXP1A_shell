//
// Created by Michal Smola on 6/13/18.
//

#include "Controller.hpp"

using namespace shell::ui;


std::atomic<bool> Controller::shouldClose = false;


void Controller::start()
{
    std::unique_ptr<shell::tasks::TasksFacade> tasksFacade(new shell::tasks::TasksFacade);
    initializeSignals();

    while (true) {
        showHeader();
        std::string command = userInterface->getNextCommand().get();
        try {
            tasksFacade->buildAndAddTask(parser->buildTree(command));
        }
        catch (std::exception &e) {
            userInterface->printError(e.what());
        }
    }
}

void Controller::showHeader()
{
    std::cout << "\nUXP1A@" << getHostName() << ":" << getCurrentDirectory() << "$ ";
}

const std::string Controller::getHostName()
{
    char hostName[HOST_NAME_SIZE];
    if (gethostname(hostName, HOST_NAME_SIZE - 1) != -1) {
        hostName[HOST_NAME_SIZE - 1] = 0;
        return (const std::string) hostName;
    }

    return UNKNOWN_HOST_NAME;
}

const std::string Controller::getCurrentDirectory()
{
    char currentDir[CURRENT_DIR_SIZE];
    if (getcwd(currentDir, CURRENT_DIR_SIZE - 1) != NULL) {
        currentDir[CURRENT_DIR_SIZE - 1] = 0;
        return (const std::string) currentDir;
    }

    return UNKNOWN_CURRENT_DIR;
}

std::unique_ptr<shell::model::variables::Variable> Controller::getVariable(const std::string &variable) const
{
    return modelFacade->getVariable(variable);
}

void Controller::setVariable(const std::string &name, const std::string &value)
{
    modelFacade->setVariable(name, value);
}

void Controller::exportVariable(const std::string &name)
{
    modelFacade->exportVariable(name);
}

void Controller::initializeSignals() const
{
    signal(SIGINT, signalHandler);
    signal(SIGTSTP, signalHandler);
    signal(SIGTTIN, SIG_IGN);
    signal(SIGTTOU, SIG_IGN);
}

void Controller::signalHandler(int sigType)
{
    if (sigType == SIGINT) {
        shouldClose = true;
    } else if (sigType == SIGTSTP) {
        std::cout << "SIGTSTP";
    }
}