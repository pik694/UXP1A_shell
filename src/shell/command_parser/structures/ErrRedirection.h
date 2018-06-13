//
// Created by Daniel Bigos on 13.06.18.
//

#ifndef UXP1A_SHELL_ERRREDIRECTION_H
#define UXP1A_SHELL_ERRREDIRECTION_H

#include "Err.h"

namespace shell::parser::structures
{
    class ErrRedirection : public Err
    {
    public:
        explicit ErrRedirection( const std::string &path );
        virtual ~ErrRedirection() = default;
    };

}
#endif //UXP1A_SHELL_ERRREDIRECTION_H
