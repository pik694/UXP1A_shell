//
// Created by Piotr Żelazko on 02.06.2018.
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
        Undefined = 69
    };

    class Token
    {
    public:
        explicit Token( TokenType type = TokenType::Undefined, std::string value = "" ) :
                type_( type ),
                value_( std::move( value ) ) { }

        Token( const Token &other ) :
            type_( other.type_),
            value_( other.value_ ) { }

            TokenType getType()
        {
            return type_;
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
