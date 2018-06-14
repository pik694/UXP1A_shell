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

        std::string getVariable();
        std::string getValue();
        void setValue( const std::string &value );

    private:
        std::string variable_;
        std::string value_;
    };
}

#endif //UXP1A_SHELL_ASSIGNMENT_H
