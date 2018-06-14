//
// Created by Daniel Bigos on 02.06.2018.
//

#ifndef UXP1A_SHELL_TOKEN_HPP
#define UXP1A_SHELL_TOKEN_HPP

#include <string>
#include <utility>

namespace shell::parser
{
    enum class TokenType: unsigned
    {
        EoF = 0,
        Semicolon = 1,
        Pipeline = 2,
        Background = 3,
        Assignment = 5,
        HereDocument = 6,
        SingleQuoteArg = 7,
        DoubleQuoteArg = 8,
        OUT_Redirect = 9,
        OUT_Append = 10,
        ERR_Redirect = 11,
        ERR_Append = 12,
        IN_Redirect = 13,
        Command = 14,
        Newline = 15,
        Undefined = 69
    };

    class Token
    {
    public:
        explicit Token( TokenType type = TokenType::Undefined, std::string value = "" ) :
                type_( type ),
                value_( std::move( value ) ) { }

        Token( const Token &other ) = default;

        Token &operator=( const Token &token )
        {
            type_ = token.type_;
            value_ = token.value_;

            return *this;
        }

        TokenType getType()
        {
            return type_;
        }

        void setType( TokenType type )
        {
            type_ = type;
        }

        void setValue( std::string value )
        {
            value_ = std::move( value );
        }

        std::string getValue()
        {
            return value_;
        }

    private:
        TokenType type_;
        std::string value_;
    };

}
#endif //UXP1A_SHELL_TOKEN_HPP
