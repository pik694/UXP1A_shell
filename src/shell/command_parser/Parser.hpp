//
// Created by Daniel Bigos on 02.06.2018.
//

#ifndef UXP1A_SHELL_PARSER_HPP
#define UXP1A_SHELL_PARSER_HPP

#include <string>
#include <list>
#include <memory>
#include <shell/command_parser/structures/CommandList.h>
#include <shell/command_parser/structures/ErrAppend.h>
#include <shell/command_parser/structures/OutAppend.h>
#include <shell/command_parser/structures/Assignment.h>
#include <shell/command_parser/structures/Pipeline.h>
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
        Token getToken();
        Token getBufferedToken();
        bool isBufferedToken();

        std::unique_ptr< structures::Command > parseCommand();
        std::unique_ptr< structures::HereDocument > parseHereDocument();
        std::unique_ptr< structures::Assignment > parseAssignment();
        std::unique_ptr< structures::Pipeline > parsePipeline();
        std::unique_ptr< structures::CommandList > parseCommandList();

        std::unique_ptr< Lexer > lexer_;
        Token bufferedToken_;

        const std::initializer_list< TokenType > endOfCommand = {
                TokenType::Semicolon,
                TokenType::Newline
        };

        const std::initializer_list< TokenType > redirectTokens_ = {
                TokenType::IN_Redirect,
                TokenType::OUT_Append,
                TokenType::OUT_Redirect,
                TokenType::ERR_Redirect,
                TokenType::ERR_Append
        };

        const std::unordered_map< TokenType, std::function< std::unique_ptr< structures::ast >() > > parserFunctions_ = {
                { TokenType::Assignment, std::bind( &Parser::parseAssignment, this ) },
                { TokenType::Command, std::bind( &Parser::parsePipeline, this ) },
                { TokenType::HereDocument, std::bind( &Parser::parseHereDocument, this ) },
                { TokenType::Newline, []() -> std::unique_ptr< structures::ast > { return nullptr; } }
        };

        const std::unordered_map< TokenType, std::function< std::unique_ptr< structures::Redirection >( std::string val ) > > redirections_ = {
                { TokenType::IN_Redirect, []( std::string val ) -> std::unique_ptr< structures::InRedirection > { return std::make_unique< structures::InRedirection >( val ); } },
                { TokenType::ERR_Redirect, []( std::string val ) -> std::unique_ptr< structures::ErrRedirection > { return std::make_unique< structures::ErrRedirection >( val ); } },
                { TokenType::ERR_Append, []( std::string val ) -> std::unique_ptr< structures::ErrAppend > { return std::make_unique< structures::ErrAppend>( val ); } },
                { TokenType::OUT_Redirect, []( std::string val ) -> std::unique_ptr< structures::OutRedirection > { return std::make_unique< structures::OutRedirection >( val ); } },
                { TokenType::OUT_Append, []( std::string val ) -> std::unique_ptr< structures::OutAppend > { return std::make_unique< structures::OutAppend>( val ); } },
        };
    };

    class ParserException : public std::runtime_error
    {
    public:
        explicit ParserException( const std::string &arg );

    };
}


#endif //UXP1A_SHELL_PARSER_HPP
