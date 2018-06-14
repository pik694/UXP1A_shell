//
// Created by Daniel Bigos on 12.06.18.
//

#include "Pipeline.h"

using namespace shell::parser::structures;

std::vector< std::unique_ptr< CommandList > > &Pipeline::getCommandsList()
{
    return commandsList_;
}

void Pipeline::addCommandList( std::unique_ptr< CommandList > &command_list )
{
    commandsList_.push_back( std::move( command_list ) );
}
