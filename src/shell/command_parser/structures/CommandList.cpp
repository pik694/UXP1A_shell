//
// Created by Daniel Bigos on 14.06.18.
//

#include <list>
#include <bits/unique_ptr.h>
#include "CommandList.h"
#include "Command.h"

using namespace shell::parser::structures;

std::vector <std::unique_ptr< Command > > &CommandList::getCommands()
{
    return commands_;
}

void CommandList::addCommand( std::unique_ptr < Command > &command )
{
    commands_.push_back( std::move( command ) );
}
