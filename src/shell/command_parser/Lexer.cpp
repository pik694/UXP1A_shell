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

    if( isalpha( streamWrapper_.peekChar() ) || isdigit( streamWrapper_.peekChar() ) || streamWrapper_.peekChar() == '/' )
        token = getArgument();
    else if( lexerFunctions_.count( streamWrapper_.peekChar() ) == 0 )
        throw LexerException( "Unexpected character at row: " + std::to_string( streamWrapper_.getRow() ) +
                              " at column: " + std::to_string( streamWrapper_.getColumn() ) );
    else
        token = lexerFunctions_.at( streamWrapper_.peekChar() )();

    return token;
}

const Token Lexer::getBackgroundToken()
{
    streamWrapper_.getChar();

    return Token( TokenType::Background );
}

const Token Lexer::getProgramCallOrBackArg()
{
    Token token;
    streamWrapper_.getChar();

    auto sign = streamWrapper_.getChar();
    if( sign == '.' )
        token.setType( TokenType::CD_Back );
    else if( sign == '/' )
    {
        std::string token_value;
        while( !isspace( streamWrapper_.peekChar() ) && !streamWrapper_.isEndOfStream() )
            token_value += streamWrapper_.getChar();

        token.setType( TokenType::ProgramExecution );
        token.setValue( token_value );
    }
    else
        throw LexerException( "Unexpected character after \'.\' at row: " + std::to_string( streamWrapper_.getRow() ) +
                              " at column: " + std::to_string( streamWrapper_.getColumn() ) );

    return token;
}

const Token Lexer::getSemicolon()
{
    streamWrapper_.getChar();

    return Token( TokenType::Semicolon );
}

const Token Lexer::getOutRedirect()
{
    Token token;

    streamWrapper_.getChar();

    if( streamWrapper_.peekChar() == '>' )
    {
        streamWrapper_.getChar();
        token.setType( TokenType::ERR_Redirect );
    }
    else
        token.setType( TokenType::OUT_Redirect );

    return token;
}

const Token Lexer::getInRedirectOrHereDocument()
{
    Token token;

    streamWrapper_.getChar();
    //here document
    if( streamWrapper_.peekChar() == '<' )
    {
        streamWrapper_.getChar();
        token.setType( TokenType::HereDocument );
    }
    //input redirection
    else
        token.setType( TokenType::IN_Redirect );

    return token;
}

const Token Lexer::getArgument()
{
    std::string token_value;
    while( !streamWrapper_.isEndOfStream() &&
           ( isalpha( streamWrapper_.peekChar() ) ||
                isdigit( streamWrapper_.peekChar() ) ||
                streamWrapper_.peekChar() == '_' ||
                streamWrapper_.peekChar() == '.' ||
                streamWrapper_.peekChar() == '/') )
    {
        token_value += streamWrapper_.getChar();
    }

    return Token( TokenType::Argument, token_value );
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

const Token Lexer::getShellCommand()
{
    std::string token_value;
    streamWrapper_.getChar();

    if( streamWrapper_.getChar() != '/' )
        throw LexerException( "Unexpected character in shell command at row: " + std::to_string( streamWrapper_.getRow() ) +
                                " at column: " + std::to_string( streamWrapper_.getColumn() ) );
    while( !isspace( streamWrapper_.peekChar() ) && !streamWrapper_.isEndOfStream() )
        token_value += streamWrapper_.getChar();

    return Token( TokenType::ShellCommand, token_value );
}

LexerException::LexerException( const std::string &msg ) : runtime_error( msg ) { }
