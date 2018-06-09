//
// Created by Daniel Bigos on 09.06.18.
//

#include <boost/test/unit_test_suite.hpp>
#include <shell/command_parser/Lexer.h>
#include <shell/command_parser/Token.hpp>
#include <boost/test/unit_test_log.hpp>
#include <boost/test/test_tools.hpp>

BOOST_AUTO_TEST_SUITE( LexerTests )
    using namespace shell::parser;

    std::string test;
    BOOST_AUTO_TEST_CASE( GivenEmptyStreamShouldReturnEoFToken )
    {
        test = "";
        std::istringstream stream( test );

        Lexer lexer( stream );
        Token token( lexer.getNextToken() );
        BOOST_CHECK( token.getType() == TokenType::EoF );
    }

    BOOST_AUTO_TEST_CASE( GivenStreamWithSomeEmptyLinesShouldReturnEoFToken )
    {
        test = '\n';
        test += '\n';
        test += '\n';

        std::istringstream stream( test );
        Lexer lexer( stream );
        Token token( lexer.getNextToken() );
        BOOST_CHECK( token.getType() == TokenType::EoF );
    }

    BOOST_AUTO_TEST_CASE( GivenStreamWithBackgroundSignLinesShouldReturnIt )
    {
        test = '&';

        std::istringstream stream( test );
        Lexer lexer( stream );
        Token token( lexer.getNextToken() );
        BOOST_CHECK( token.getType() == TokenType::Background );
    }

BOOST_AUTO_TEST_SUITE_END()