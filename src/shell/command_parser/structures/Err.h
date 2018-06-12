//
// Created by Daniel Bigos on 13.06.18.
//

#ifndef UXP1A_SHELL_ERR_H
#define UXP1A_SHELL_ERR_H

#include "Redirection.h"

namespace shell::parser::structures
{
    class Err : public Redirection
    {
    public:
        explicit Err( const std::string &path );
        virtual ~Err() = default;
    };
}

#endif //UXP1A_SHELL_ERR_H
