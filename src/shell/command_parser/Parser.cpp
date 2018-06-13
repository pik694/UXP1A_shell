//
// Created by Daniel Bigos on 02.06.2018.
//

#include <sstream>
#include <shell/command_parser/structures/Assignment.h>
#include "Parser.hpp"

using namespace shell::parser;
using namespace shell::parser::structures;

std::unique_ptr< ast > Parser::buildTree( const std::string & shell_command )
{
    std::istringstream ss( shell_command );

    lexer_ = std::make_unique< Lexer >( ss );

    bufferedToken_ = Token( TokenType::Undefined );

    return parseCommand();
}

Parser::Parser()
{
    lexer_ = nullptr;
}

std::unique_ptr< ast > Parser::parseCommand()
{
    if( parserFunctions_.count( peekNextToken() ) == 0 )
        throw ParserException( "Unexpected token at row: " + std::to_string( lexer_->getCurrentRow() ) +
                                " at column: " + std::to_string( lexer_->getCurrentColumn() ) );
    return parserFunctions_.at( peekNextToken() )();
}

TokenType Parser::peekNextToken()
{
    if( !isBufferedToken() )
        bufferedToken_ = lexer_->getNextToken();

    return TokenType::Undefined;// bufferedToken_.getType();
}

Token Parser::getExpectedToken( std::list< TokenType > expected_tokens )
{
    Token token = isBufferedToken() ? getBufferedToken() : lexer_->getNextToken();

    if( std::find( expected_tokens.begin(), expected_tokens.end(), token.getType() ) == expected_tokens.end() )
        throw std::runtime_error( "Unexpected token at line:" + std::to_string( lexer_->getCurrentRow() ) +
                                  " at position:" + std::to_string( lexer_->getCurrentColumn() ) );

    return token;
}

Token Parser::getBufferedToken()
{
    if( !isBufferedToken() )
        throw std::runtime_error( "Trying to get unbuffered token" );

    Token token = bufferedToken_;
    bufferedToken_ = Token( TokenType::Undefined );

    return token;
}

bool Parser::isBufferedToken()
{
    return false;
}

std::unique_ptr< ast > Parser::parseHereDocument()
{
    return nullptr;
}


std::unique_ptr< structures::ast > Parser::parseAssignment()
{
    return nullptr;
}

std::unique_ptr< structures::ast > Parser::parsePipeline()
{
    return nullptr;
}

ParserException::ParserException( const std::string &arg ) : runtime_error( arg ) { }
