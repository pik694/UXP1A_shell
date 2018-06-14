//
// Created by Piotr Żelazko on 13.06.2018.
//

#include <sys/stat.h>
#include <sys/errno.h>
#include <unistd.h>
#include <system_error>
#include <fcntl.h>
#include "Pipeline.hpp"

using namespace shell::tasks;

const std::string Pipeline::PIPELINES_PATH = "/tmp/uxp1a_shell/pipelines/";

Pipeline::Pipeline() {

    int i = 0;

    while (!createFifo(i++));


    inDescriptor_ = open(name_.c_str(), O_RDONLY | O_NONBLOCK);
    outDescriptor_ = open(name_.c_str(), O_WRONLY | O_NONBLOCK);

    if (inDescriptor_ == -1 || outDescriptor_ == -1)
        throw std::system_error(errno, std::system_category());


}

bool Pipeline::createFifo(int seq) {



    auto tmpName = PIPELINES_PATH + "pipe" + std::to_string(seq);

    auto status = mkfifo(tmpName.c_str(), 0666);

    if (status == 0) {
        name_ = std::move(tmpName);
        return true;
    }
    else if (errno != EEXIST)
        throw std::system_error(errno, std::system_category());

    return false;

}

Pipeline::~Pipeline() {

    if(!name_.empty())
        unlink(name_.c_str());

    close(inDescriptor_);
    close(outDescriptor_);
}

int Pipeline::getInDescriptor() const {
    return inDescriptor_;
}

int Pipeline::getOutDescriptor() const {
    return outDescriptor_;
}

const std::string &Pipeline::getName() const {
    return name_;
}

