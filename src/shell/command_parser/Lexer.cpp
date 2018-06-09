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

    return token;
}

void Lexer::skipWhitespaces()
{
    while( std::isspace( streamWrapper_.peekChar() ) )
        streamWrapper_.getChar();
}

LexerException::LexerException( const std::string &msg ) : runtime_error( msg ) { }
