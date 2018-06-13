//
// Created by Daniel Bigos on 13.06.18.
//

#ifndef UXP1A_SHELL_ERRAPPEND_H
#define UXP1A_SHELL_ERRAPPEND_H

#include "Err.h"

namespace shell::parser::structures
{
    class ErrAppend : public Err
    {
    public:
        explicit ErrAppend( const std::string &path );
        virtual ~ErrAppend() = default;

    };
}

#endif //UXP1A_SHELL_ERRAPPEND_H
