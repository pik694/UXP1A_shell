//
// Created by Daniel Bigos on 02.06.2018.
//

#include <sstream>
#include "Parser.hpp"

using namespace shell::parser;
using namespace shell::parser::structures;

std::unique_ptr< ast > Parser::buildTree( const std::string & shell_command )
{
    std::istringstream ss( shell_command );

    lexer_ = std::make_unique< Lexer >( ss );

    return parseCommand();
}

Parser::Parser()
{
    lexer_ = nullptr;
}

std::unique_ptr< ast > Parser::parseCommand()
{
    return std::unique_ptr< ast >();
}
