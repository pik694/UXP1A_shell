//
// Created by Piotr Żelazko on 13.06.2018.
//

#include <sys/stat.h>
#include <sys/errno.h>
#include <system_error>
#include "Pipeline.hpp"

using namespace shell::tasks;

const std::string Pipeline::PIPELINES_PATH = "~/.uxp1a_shell/pipelines/";

Pipeline::Pipeline() {

    int i = 0;

    while (!createFifo(i++));



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
}

