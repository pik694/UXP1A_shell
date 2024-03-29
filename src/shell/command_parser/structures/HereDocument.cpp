//
// Created by Daniel Bigos on 12.06.18.
//

#include "HereDocument.h"

using namespace shell::parser::structures;

std::unique_ptr<shell::tasks::Task> HereDocument::accept( Visitor &visitor )
{
    return visitor.visit( *this );
}
