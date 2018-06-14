//
// Created by Daniel Bigos on 12.06.18.
//

#include <string>
#include "Assignment.h"

using namespace shell::parser::structures;

Assignment::Assignment( const std::string &variable ) : variable_( variable ) { }

std::string Assignment::getVariable()
{
    return variable_;
}

std::string Assignment::getValue()
{
    return value_;
}

void Assignment::setValue( const std::string &value )
{
    value_ = value;
}
