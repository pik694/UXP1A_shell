//
// Created by Daniel Bigos on 12.06.18.
//

#include "Pipeline.h"

using namespace shell::parser::structures;

std::list< std::unique_ptr< Command > > &Pipeline::getCommands()
{
    return commands_;
}

void Pipeline::addCommand( std::unique_ptr< Command > &program )
{
    commands_.push_back( std::move( program ) );
}
