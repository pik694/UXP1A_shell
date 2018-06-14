//
// Created by Piotr Żelazko on 09.06.2018.
//

#include <shell/tasks/domain/tasks/decorator/PipelinedTask.hpp>
#include <shell/tasks/domain/tasks/decorator/BackgroundTask.hpp>
#include "PipelinedTasks.hpp"
#include "Pipeline.hpp"

using namespace shell::tasks;

PipelinedTasks::PipelinedTasks(TasksManager &manager, std::list<std::unique_ptr<Task>> tasks) : manager_(
        manager), tasks_(std::move(tasks)) {}

boost::optional<pid_t> PipelinedTasks::run() {

    auto writerIt = tasks_.begin();
    auto readerIt = ++tasks_.begin();

    std::shared_ptr<Pipeline> inPipeline = nullptr;
    std::shared_ptr<Pipeline> outPipeline = nullptr;

    for (; readerIt != tasks_.end(); ++writerIt, ++readerIt){

        outPipeline = std::make_shared<Pipeline>();

        *writerIt = std::unique_ptr<Task>(new decorators::PipelinedTask(std::move(*writerIt), inPipeline, outPipeline));

        inPipeline = outPipeline;
        outPipeline = nullptr;

    }

    *writerIt = std::unique_ptr<Task>(new decorators::PipelinedTask(std::move(*writerIt), inPipeline, outPipeline));


    for (auto taskIterator = tasks_.begin(); taskIterator != tasks_.end(); ++taskIterator)
        manager_.addTask(std::move(*taskIterator));



 return boost::none;

}
