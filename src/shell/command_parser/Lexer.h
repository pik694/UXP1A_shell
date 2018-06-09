//
// Created by Daniel Bigos on 09.06.18.
//

#ifndef UXP1A_SHELL_LEXER_H
#define UXP1A_SHELL_LEXER_H

#include <istream>
#include "Token.hpp"

namespace shell::parser
{
    class LexerException : public std::runtime_error
    {
    public:
        LexerException( const std::string &msg );
    };

    class Lexer
    {
    public:
        explicit Lexer( std::istream &input_stream );
        ~Lexer() = default;

        const Token getNextToken();

    private:
        class StreamWrapper
        {
        public:
            StreamWrapper( std::istream& input_stream ) :
                      inputStream_( input_stream ) { }

            char getChar()
            {
                char sign;
                inputStream_.get( sign );
                return sign;
            }

            char peekChar()
            {
                return static_cast< char >( inputStream_.peek() );
            }

            bool isEndOfStream()
            {
                return inputStream_.eof();
            }

        private:
            std::istream &inputStream_;
        };

        StreamWrapper streamWrapper_;
    };


}

#endif //UXP1A_SHELL_LEXER_H
