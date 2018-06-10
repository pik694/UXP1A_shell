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
        Semicolon = 1,
        Pipeline = 2,
        Background = 3,
        Flag = 4,
        ProgramExecution = 5,
        ShellCommand = 6,
        Assignment = 7,
        CD_Back = 8,
        OUT_Redirect = 9,
        ERR_Redirect = 10,
        IN_Redirect = 11,
        Argument = 12,
        SingleQuoteArg = 13,
        DoubleQuoteArg = 14,
        HereDocument = 15,
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
