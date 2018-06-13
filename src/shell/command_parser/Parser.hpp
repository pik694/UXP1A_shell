//
// Created by Daniel Bigos on 02.06.2018.
//

#ifndef UXP1A_SHELL_PARSER_HPP
#define UXP1A_SHELL_PARSER_HPP

#include <string>
#include <list>
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

        TokenType peekNextToken();
        Token getExpectedToken( std::list< TokenType  > expected_tokens );
        Token getBufferedToken();
        bool isBufferedToken();

        std::unique_ptr< structures::ast > parseCommand();
        std::unique_ptr< structures::ast > parseHereDocument();
        std::unique_ptr< structures::ast > parseAssignment();
        std::unique_ptr< structures::ast > parsePipeline();

        std::unique_ptr< Lexer > lexer_;
        Token bufferedToken_;

        const std::initializer_list< TokenType > endOfCommand = {
                TokenType::Semicolon,
                TokenType::Newline
        };

        const std::unordered_map< TokenType, std::function< std::unique_ptr< structures::ast >() > > parserFunctions_ = {
                { TokenType::Assignment, std::bind( &Parser::parseAssignment, this ) },
                { TokenType::Command, std::bind( &Parser::parsePipeline, this ) },
                { TokenType::HereDocument, std::bind( &Parser::parseHereDocument, this ) }
        };

    };

    class ParserException : public std::runtime_error
    {
    public:
        explicit ParserException( const std::string &arg );

    };
}


#endif //UXP1A_SHELL_PARSER_HPP
