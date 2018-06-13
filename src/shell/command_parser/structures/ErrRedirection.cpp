//
// Created by Daniel Bigos on 13.06.18.
//

#include "ErrRedirection.h"

using namespace shell::parser::structures;

ErrRedirection::ErrRedirection( const std::string &path ) : Err( path ) { }
