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

    return token;
}

LexerException::LexerException( const std::string &msg ) : runtime_error( msg ) { }
