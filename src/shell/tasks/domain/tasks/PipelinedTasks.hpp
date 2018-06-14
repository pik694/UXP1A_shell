//
// Created by Piotr Żelazko on 09.06.2018.
//

#ifndef UXP1A_SHELL_PIPELINEDTASKS_HPP
#define UXP1A_SHELL_PIPELINEDTASKS_HPP

#include <memory>
#include <list>
#include <shell/tasks/domain/TasksManager.hpp>
#include "Task.hpp"

namespace shell::tasks {
    class PipelinedTasks : public Task {
    public:

        PipelinedTasks(TasksManager &manager, std::list<std::unique_ptr<Task>> tasks);

        boost::optional<pid_t> run() override;

    private:
        TasksManager& manager_;
        std::list<std::unique_ptr<Task>> tasks_;
    };
}


#endif //UXP1A_SHELL_PIPELINEDTASKS_HPP
