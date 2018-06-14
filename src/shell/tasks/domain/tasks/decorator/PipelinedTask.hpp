//
// Created by Piotr Żelazko on 14.06.2018.
//

#ifndef UXP1A_SHELL_PIPELINEDTASK_HPP
#define UXP1A_SHELL_PIPELINEDTASK_HPP

#include <shell/tasks/domain/tasks/Pipeline.hpp>
#include "TaskDecorator.hpp"

namespace shell::tasks::decorators {
    class PipelinedTask : public TaskDecorator{
    public:
        PipelinedTask(std::unique_ptr<Task> decoratedTask, const std::shared_ptr<Pipeline> &in,
                      const std::shared_ptr<Pipeline> &out);

        bool isBackgroundTask() override;

    private:
        std::shared_ptr<Pipeline> in_;
        std::shared_ptr<Pipeline> out_;
    };
}


#endif //UXP1A_SHELL_PIPELINEDTASK_HPP
