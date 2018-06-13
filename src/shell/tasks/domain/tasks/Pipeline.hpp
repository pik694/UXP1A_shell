//
// Created by Piotr Żelazko on 02.06.2018.
//

#ifndef UXP1A_SHELL_PIPELINE_HPP
#define UXP1A_SHELL_PIPELINE_HPP

#include <memory>
#include <string>
#include "Task.hpp"

namespace shell::tasks{

    class Pipeline {
    public:
        Pipeline();

        int getInDescriptor() const;

        int getOutDescriptor() const;

        const std::string &getName() const;

        virtual ~Pipeline();

    private:

        bool createFifo(int seq);

        std::string name_;
        int inDescriptor_;
        int outDescriptor_;

        static const std::string PIPELINES_PATH;
    };
}


#endif //UXP1A_SHELL_PIPELINE_HPP
