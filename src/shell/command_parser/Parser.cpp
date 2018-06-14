//
// Created by Daniel Bigos on 02.06.2018.
//

#include <sstream>
#include <shell/command_parser/structures/Assignment.h>
#include <shell/command_parser/structures/Pipeline.h>
#include <shell/ui/Controller.hpp>
#include <regex>
#include "Parser.hpp"

using namespace shell::parser;
using namespace shell::parser::structures;

std::unique_ptr< ast > Parser::buildTree( const std::string & shell_command )
{
    std::istringstream ss( shell_command );

    lexer_ = std::make_unique< Lexer >( ss );

    bufferedToken_ = Token( TokenType::Undefined );

    if( parserFunctions_.count( peekNextToken() ) == 0 )
        throw ParserException( "Unexpected token at line:" + std::to_string( lexer_->getCurrentRow() ) +
                               " at position:" + std::to_string( lexer_->getCurrentColumn() ) );

    return parserFunctions_.at( peekNextToken() )();
}

Parser::Parser()
{
    lexer_ = nullptr;
}

std::unique_ptr< structures::Command > Parser::parseCommand()
{
    auto command = std::make_unique< structures::Command >( getExpectedToken( { TokenType::Command } ).getValue() );

    while( peekNextToken() == TokenType::Command || peekNextToken() == TokenType::DoubleQuoteArg ){
        std::string variable_value = getExpectedToken( { TokenType::Command, TokenType::DoubleQuoteArg } ).getValue() ;
        while( true )
        {
            std::size_t found = variable_value.find( '$' );
            if( found == std::string::npos )
                break;

            std::string variable, new_value;
            for( size_t i = found+1; i < variable_value.length() && !isspace( variable_value[ i ] ); ++i )
                variable += variable_value[ i ];

            new_value = shell::ui::Controller::getInstance().getVariable( variable )->getStringValues();
            variable_value = std::regex_replace( variable_value, std::regex( "\\$" + variable ), new_value );
        }
        command->addArgument( variable_value );
    }

    if( peekNextToken() == TokenType::Background )
    {
        getExpectedToken( { TokenType::Background } );
        command->setBackgroundExecution();
    }

    while( peekNextToken() == TokenType::IN_Redirect || peekNextToken() == TokenType::ERR_Append || peekNextToken() == TokenType::OUT_Append ||
            peekNextToken() == TokenType::ERR_Redirect || peekNextToken() == TokenType::OUT_Redirect )
    {
        auto redirection = redirections_.at( getExpectedToken( redirectTokens_ ).getType() )( getExpectedToken( { TokenType::Command } ).getValue() );
        command->addRedirection( redirection );
    }

    if( peekNextToken() == TokenType::HereDocument )
    {
        auto here_document = parseHereDocument();
        command->addHereDocument( here_document );
    }

    return command;
}

TokenType Parser::peekNextToken()
{
    if( !isBufferedToken() )
        bufferedToken_ = lexer_->getNextToken();

    return bufferedToken_.getType();
}

Token Parser::getExpectedToken( std::list< TokenType > expected_tokens )
{
    Token token = getToken();

    if( std::find( expected_tokens.begin(), expected_tokens.end(), token.getType() ) == expected_tokens.end() )
        throw ParserException( "Unexpected token at line:" + std::to_string( lexer_->getCurrentRow() ) +
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
    return bufferedToken_.getType() != TokenType::Undefined;
}

std::unique_ptr< structures::HereDocument > Parser::parseHereDocument()
{
    //TODO
    //it only removes tokens

    std::string here_document = getExpectedToken( { TokenType::HereDocument } ).getValue();

    while( peekNextToken() != TokenType::EoF && getToken().getValue() != here_document );

    if( peekNextToken() == TokenType::EoF )
        throw ParserException( "Here document without ending" );

    return nullptr;
}


std::unique_ptr< structures::Assignment > Parser::parseAssignment()
{
    auto assignment = std::make_unique< structures::Assignment >( getExpectedToken( { TokenType::Assignment } ).getValue() );

    Token token = getExpectedToken( { TokenType::Command, TokenType::SingleQuoteArg, TokenType::DoubleQuoteArg } );
    std::string variable_value = token.getValue();
    //replace environment variables by theirs values
    if( token.getType() == TokenType::DoubleQuoteArg || token.getType() == TokenType::Command )
    {
        while( true )
        {
            std::size_t found = variable_value.find( '$' );
            if( found == std::string::npos )
                break;

            std::string variable, new_value;
            for( size_t i = found+1; i < variable_value.length() && !isspace( variable_value[ i ] ); ++i )
                variable += variable_value[ i ];

            new_value = shell::ui::Controller::getInstance().getVariable( variable )->getStringValues();
            variable_value = std::regex_replace( variable_value, std::regex( "\\$" + variable ), new_value );
        }
    }

    assignment->setValue( variable_value );
    return assignment;
}

std::unique_ptr< structures::Pipeline > Parser::parsePipeline()
{
    auto pipeline = std::make_unique< structures::Pipeline >();

    do
    {
        auto command_list = parseCommandList();
        pipeline->addCommandList( command_list );
    }
    while( [&]() -> bool
    {
        if( peekNextToken() == TokenType::Pipeline )
        {
            getExpectedToken( {TokenType::Pipeline } );
            return true;
        }
        else
            return false;
    }() );

    return pipeline;
}

std::unique_ptr< structures::CommandList > Parser::parseCommandList()
{
    auto command_list = std::make_unique< CommandList >();

    do
    {
       auto command = parseCommand();
       command_list->addCommand( command );
    }
    while( [&]() -> bool
    {
       if( peekNextToken() == TokenType::Semicolon )
       {
           getExpectedToken( {TokenType::Semicolon } );
           return true;
       }
       else
           return false;
    }() );

    return command_list;
}

Token Parser::getToken()
{
    return isBufferedToken() ? getBufferedToken() : lexer_->getNextToken();
}

ParserException::ParserException( const std::string &arg ) : runtime_error( arg ) { }
