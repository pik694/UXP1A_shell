//
// Created by Daniel Bigos on 12.06.18.
//

#ifndef UXP1A_SHELL_HEREDOCUMENT_H
#define UXP1A_SHELL_HEREDOCUMENT_H

#include "AbstractSyntaxTree.hpp"

namespace shell::parser::structures
{
    class HereDocument : public AbstractSyntaxTree
    {
    public:
        explicit HereDocument() = default;
        virtual ~HereDocument() = default;
    };
}
#endif //UXP1A_SHELL_HEREDOCUMENT_H
