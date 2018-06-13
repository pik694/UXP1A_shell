//
// Created by Daniel Bigos on 09.06.2018.
//

#ifndef UXP1A_SHELL_ABSTRACTSYNTAXTREE_HPP
#define UXP1A_SHELL_ABSTRACTSYNTAXTREE_HPP

namespace shell::parser::structures
{

    class AbstractSyntaxTree
    {
    public:
        explicit AbstractSyntaxTree() = default;
        virtual ~AbstractSyntaxTree() = default;
    };


    using ast = AbstractSyntaxTree;
}


#endif //UXP1A_SHELL_ABSTRACTSYNTAXTREE_HPP
