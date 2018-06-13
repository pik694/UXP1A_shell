//
// Created by Daniel Bigos on 12.06.18.
//

#include "ProgramExecution.h"

using namespace shell::parser::structures;

ProgramExecution::ProgramExecution()
{
    inRedirection_ = nullptr;
    outRedirection_ = nullptr;
    errRedirection_ = nullptr;
}

Out *ProgramExecution::getOutRedirection()
{
    return outRedirection_ != nullptr ? outRedirection_.get() : nullptr;
}

Err *ProgramExecution::getErrRedirection()
{
    return errRedirection_ != nullptr ? errRedirection_.get() : nullptr;
}

InRedirection *ProgramExecution::getInRedirection()
{
    return inRedirection_ != nullptr ? inRedirection_.get() : nullptr;
}

void ProgramExecution::addInRedirection( std::unique_ptr< InRedirection > & ptr )
{
    inRedirection_ = std::move( ptr );
}

void ProgramExecution::addOutRedirection( std::unique_ptr< OutRedirection > & ptr )
{
    outRedirection_ =  std::move( ptr );
}

void ProgramExecution::addErrRedirection( std::unique_ptr< ErrRedirection > & ptr )
{
    errRedirection_ = std::move( ptr );
}
