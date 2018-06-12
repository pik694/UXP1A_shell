//
// Created by Daniel Bigos on 02.06.2018.
//

#ifndef UXP1A_SHELL_PARSER_HPP
#define UXP1A_SHELL_PARSER_HPP

#include <string>
#include <memory>
#include "shell/command_parser/structures/AbstractSyntaxTree.hpp"
#include "Lexer.h"

namespace shell::parser
{
    class Parser
    {
    public:
        explicit Parser();
        ~Parser() = default;

        std::unique_ptr< structures::ast > buildTree( const std::string& );

    private:

        std::unique_ptr < structures::ast > parseCommand();
        std::unique_ptr< Lexer > lexer_;
    };
}


#endif //UXP1A_SHELL_PARSER_HPP
