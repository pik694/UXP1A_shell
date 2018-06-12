//
// Created by Daniel Bigos on 13.06.18.
//

#ifndef UXP1A_SHELL_INREDIRECTION_H
#define UXP1A_SHELL_INREDIRECTION_H

#include "Redirection.h"

namespace shell::parser::structures
{
    class InRedirection : public Redirection
    {
    public:
        explicit InRedirection( const std::string &path );
        virtual ~InRedirection() = default;
    };
}

#endif //UXP1A_SHELL_INREDIRECTION_H
