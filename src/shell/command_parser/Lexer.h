//
// Created by Daniel Bigos on 09.06.18.
//

#ifndef UXP1A_SHELL_LEXER_H
#define UXP1A_SHELL_LEXER_H

#include <istream>
#include <unordered_map>
#include <functional>
#include "Token.hpp"

const unsigned START_COL = 1;

namespace shell::parser
{
    class LexerException : public std::runtime_error
    {
    public:
        explicit LexerException( const std::string &msg );
    };

    class Lexer
    {
    public:
        explicit Lexer( std::istream &input_stream );
        ~Lexer() = default;

        const Token getNextToken();
        size_t getCurrentRow();
        size_t getCurrentColumn();

    private:
        class StreamWrapper
        {
        public:
            explicit StreamWrapper( std::istream& input_stream ) :
                    row_( 0 ),
                    column_( 0 ),
                    inputStream_( input_stream ) { }

            size_t getColumn() { return column_; }
            size_t getRow() { return row_; }

            char getChar()
            {
                char sign;
                inputStream_.get( sign );

                if( sign == '\n' )
                {
                    ++row_;
                    column_ = START_COL;
                }
                else
                {
                    ++column_;
                }

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
            size_t row_{};
            size_t column_{};
            std::istream &inputStream_;
        };

        std::unordered_map< char, std::function< const Token()> > lexerFunctions_ = {
                { '&', std::bind( &Lexer::getBackgroundToken, this ) },
                { ';', std::bind( &Lexer::getSemicolon, this ) },
                { '|', std::bind( &Lexer::getPipelineSign, this ) },
                { '\"', std::bind( &Lexer::getDoubleQuoteArgument, this ) },
                { '\'', std::bind( &Lexer::getSingleQuoteArgument, this ) },
                { '\n', std::bind( &Lexer::getNewline, this ) }
        };

        std::unordered_map< std::string, TokenType > keySymbols_ = {
                { "1>", TokenType::OUT_Redirect },
                { "1>>", TokenType::OUT_Append },
                { "2>", TokenType::ERR_Redirect },
                { "2>>", TokenType::ERR_Append },
                { "<", TokenType::IN_Redirect },
        };
        StreamWrapper streamWrapper_;

        void skipWhitespaces();

        const Token getSemicolon();
        const Token getToken();
        const Token getBackgroundToken();
        const Token getPipelineSign();
        const Token getDoubleQuoteArgument();
        const Token getSingleQuoteArgument();
        const Token getCommand();
        const Token getNewline();
    };


}

#endif //UXP1A_SHELL_LEXER_H
