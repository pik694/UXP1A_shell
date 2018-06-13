//
// Created by Piotr Żelazko on 14.06.2018.
//

#include "PipelinedTask.hpp"
#include "StandardOutputRedirector.hpp"
#include "StandardInputRedirector.hpp"

shell::tasks::decorators::PipelinedTask::PipelinedTask(std::unique_ptr<shell::tasks::Task> decoratedTask,
                                                       std::shared_ptr<shell::tasks::Pipeline> const& in = nullptr,
                                                       std::shared_ptr<shell::tasks::Pipeline> const& out = nullptr)
        : TaskDecorator(std::move(decoratedTask)), in_(in), out_(out){

    if (out_){
        decoratedTask_ = std::unique_ptr<Task>(new StandardOutputRedirector(std::move(decoratedTask), out_->getInDescriptor()));
    }
    if (in_){
        decoratedTask_ = std::unique_ptr<Task>(new StandardInputRedirector(std::move(decoratedTask), in_->getOutDescriptor()));
    }

}