//
// Created by Daniel Bigos on 09.06.18.
//

#include "Lexer.h"

using namespace shell::parser;

Lexer::Lexer( std::istream &input_stream ) :
    streamWrapper_( input_stream ) { }

const Token Lexer::getNextToken()
{
    Token token;

    skipWhitespaces();

    if( streamWrapper_.isEndOfStream() )
        token.setType( TokenType::EoF );
    else
        token = getToken();

    return token;
}

void Lexer::skipWhitespaces()
{
    while( std::isspace( streamWrapper_.peekChar() ) )
        streamWrapper_.getChar();
}

const Token Lexer::getToken()
{
    Token token;

    if( lexerFunctions_.count( streamWrapper_.peekChar() ) == 1 )
        token = lexerFunctions_.at( streamWrapper_.peekChar() )();
    else token = getCommand();


    return token;
}

const Token Lexer::getBackgroundToken()
{
    streamWrapper_.getChar();

    return Token( TokenType::Background );
}

const Token Lexer::getSemicolon()
{
    streamWrapper_.getChar();

    return Token( TokenType::Semicolon );
}

const Token Lexer::getAssignmentSign()
{
    streamWrapper_.getChar();

    return Token( TokenType::Assignment );
}

const Token Lexer::getPipelineSign()
{
    streamWrapper_.getChar();

    return Token( TokenType::Pipeline );
}

size_t Lexer::getCurrentRow()
{
    return streamWrapper_.getRow();
}

size_t Lexer::getCurrentColumn()
{
    return streamWrapper_.getColumn();
}

const Token Lexer::getDoubleQuoteArgument()
{
    std::string buffer;
    //skip double quote
    streamWrapper_.getChar();
    do
    {
        char sign = streamWrapper_.getChar();
        if( sign == '\"' )
            buffer.at( buffer.length() - 1 ) = sign;
        else
            buffer.push_back( sign );
    }
    while( ( streamWrapper_.peekChar() != '\"' ||
             ( streamWrapper_.peekChar() == '\"' && buffer.at( buffer.length() - 1 ) == '\\' ) )
           && !streamWrapper_.isEndOfStream() );

    if( streamWrapper_.getChar() != '\"' )
        throw LexerException( "Token without closing double quote" );

    return Token( TokenType::DoubleQuoteArg, buffer );
}

const Token Lexer::getSingleQuoteArgument()
{
    std::string buffer;
    //skip single quote
    streamWrapper_.getChar();
    do
    {
        char sign = streamWrapper_.getChar();
        if( sign == '\'' )
            buffer.at( buffer.length() - 1 ) = sign;
        else
            buffer.push_back( sign );
    }
    while( ( streamWrapper_.peekChar() != '\'' ||
             ( streamWrapper_.peekChar() == '\'' && buffer.at( buffer.length() - 1 ) == '\\' ) )
           && !streamWrapper_.isEndOfStream() );

    if( streamWrapper_.getChar() != '\'')
        throw LexerException( "Token without closing single quote" );

    return Token( TokenType::SingleQuoteArg, buffer );
}

const Token Lexer::getFlag()
{
    streamWrapper_.getChar();

    auto flag = streamWrapper_.getChar();
    if( !isalpha( flag ) )
        throw LexerException( "Unexpected character as a flag at row: " + std::to_string( streamWrapper_.getRow() ) +
                                " at col: " + std::to_string( streamWrapper_.getColumn() ) );

    return Token( TokenType::Flag, std::string( 1, flag ) );
}

const Token Lexer::getCommand()
{
    Token token( TokenType::Command );
    std::string token_value;

    while( !isspace( streamWrapper_.peekChar() ) && !streamWrapper_.isEndOfStream() )
        token_value +=  streamWrapper_.getChar();

    if( keySymbols_.count( token_value ) == 1 )
        token.setType( keySymbols_[ token_value ] );
    else if( token_value.size() > 2 &&  token_value.substr( 0, 2) == "<<" )
    {
        token.setType( TokenType::HereDocument );
        token.setValue( token_value.substr( 2, token_value.size() - 2 ) );
    }
    else
        token.setValue( token_value );
    return token;
}

LexerException::LexerException( const std::string &msg ) : runtime_error( msg ) { }
