//
// Created by Daniel Bigos on 12.06.18.
//

#ifndef UXP1A_SHELL_ASSIGNMENT_H
#define UXP1A_SHELL_ASSIGNMENT_H

#include "AbstractSyntaxTree.hpp"

namespace shell::parser::structures
{
    class Assignment : public AbstractSyntaxTree
    {
    public:
        explicit Assignment() = default;
        virtual ~Assignment() = default;

    };
}

#endif //UXP1A_SHELL_ASSIGNMENT_H
