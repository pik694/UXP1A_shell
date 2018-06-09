//
// Created by Daniel Bigos on 02.06.2018.
//

#ifndef UXP1A_SHELL_PARSER_HPP
#define UXP1A_SHELL_PARSER_HPP

#include <string>
#include "AbstractSyntaxTree.hpp"

namespace shell::parser {
    class Parser {

        //TODO: gets a string command and produces a tree
        std::unique_ptr<ast> buildTree(const std::string&);
    };
}


#endif //UXP1A_SHELL_PARSER_HPP
