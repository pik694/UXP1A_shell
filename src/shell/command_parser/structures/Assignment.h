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
        explicit Assignment( const std::string &variable );
        virtual ~Assignment() = default;

    private:
        std::string variable_;
    };
}

#endif //UXP1A_SHELL_ASSIGNMENT_H
