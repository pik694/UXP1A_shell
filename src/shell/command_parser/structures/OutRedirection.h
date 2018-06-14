//
// Created by Daniel Bigos on 13.06.18.
//

#ifndef UXP1A_SHELL_OUTREDIRECTION_H
#define UXP1A_SHELL_OUTREDIRECTION_H

#include "Out.h"

namespace shell::parser::structures
{
    class OutRedirection : public Out
    {
    public:
        explicit OutRedirection( const std::string &path );
        virtual ~OutRedirection() = default;
    };
}
#endif //UXP1A_SHELL_OUTREDIRECTION_H
