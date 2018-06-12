//
// Created by Daniel Bigos on 12.06.18.
//

#include "Pipeline.h"

using namespace shell::parser::structures;

std::list< std::unique_ptr< ProgramExecution > > &Pipeline::getPrograms()
{
    return programs_;
}

void Pipeline::addProgram( std::unique_ptr< ProgramExecution > & program )
{
    programs_.push_back( std::move( program ) );
}
