//
// Created by Daniel Bigos on 12.06.18.
//

#include "Command.h"

using namespace shell::parser::structures;

Command::Command()
{
    inRedirection_ = nullptr;
    outRedirection_ = nullptr;
    errRedirection_ = nullptr;
}

Out *Command::getOutRedirection()
{
    return outRedirection_ != nullptr ? outRedirection_.get() : nullptr;
}

Err *Command::getErrRedirection()
{
    return errRedirection_ != nullptr ? errRedirection_.get() : nullptr;
}

InRedirection *Command::getInRedirection()
{
    return inRedirection_ != nullptr ? inRedirection_.get() : nullptr;
}

void Command::addInRedirection( std::unique_ptr< InRedirection > & ptr )
{
    inRedirection_ = std::move( ptr );
}

void Command::addOutRedirection( std::unique_ptr< OutRedirection > & ptr )
{
    outRedirection_ =  std::move( ptr );
}

void Command::addErrRedirection( std::unique_ptr< ErrRedirection > & ptr )
{
    errRedirection_ = std::move( ptr );
}
