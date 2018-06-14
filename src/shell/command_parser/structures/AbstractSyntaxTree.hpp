//
// Created by Daniel Bigos on 09.06.2018.
//

namespace shell::parser::structures
{
    class Visitor;
}

#ifndef UXP1A_SHELL_ABSTRACTSYNTAXTREE_HPP
#define UXP1A_SHELL_ABSTRACTSYNTAXTREE_HPP

#include "Visitor.h"

namespace shell::parser::structures
{

    class AbstractSyntaxTree
    {
    public:
        explicit AbstractSyntaxTree() = default;
        virtual ~AbstractSyntaxTree() = default;

        virtual std::unique_ptr<shell::tasks::Task> accept( Visitor &visitor ) = 0;
    };


    using ast = AbstractSyntaxTree;
}


#endif //UXP1A_SHELL_ABSTRACTSYNTAXTREE_HPP
