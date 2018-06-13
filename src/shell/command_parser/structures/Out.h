//
// Created by Daniel Bigos on 13.06.18.
//

#ifndef UXP1A_SHELL_OUT_H
#define UXP1A_SHELL_OUT_H

#include "Redirection.h"

namespace shell::parser::structures
{
    class Out : public Redirection
    {
    public:
        explicit Out( const std::string &path );
        virtual ~Out() = default;
    };
}
#endif //UXP1A_SHELL_OUT_H
