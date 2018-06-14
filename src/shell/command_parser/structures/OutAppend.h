//
// Created by Daniel Bigos on 13.06.18.
//

#ifndef UXP1A_SHELL_OUTAPPEND_H
#define UXP1A_SHELL_OUTAPPEND_H

#include "Out.h"

namespace shell::parser::structures
{
    class OutAppend : public Out
    {
    public:
        explicit OutAppend( const std::string &path );
        virtual ~OutAppend() = default;
    };
}
#endif //UXP1A_SHELL_OUTAPPEND_H
