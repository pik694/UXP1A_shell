//
// Created by Daniel Bigos on 13.06.18.
//

#include "Redirection.h"

using namespace shell::parser::structures;

Redirection::Redirection( const std::string &path ) :
        path_( path ) { }

std::string Redirection::getPath()
{
    return path_;
}
