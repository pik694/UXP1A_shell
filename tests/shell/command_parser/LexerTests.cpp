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
        test = "\n";
        test += "\n";
        test += "\n";

        std::istringstream stream( test );
        Lexer lexer( stream );
        Token token( lexer.getNextToken() );
        BOOST_CHECK( token.getType() == TokenType::EoF );
    }

    BOOST_AUTO_TEST_CASE( GivenStreamWithBackgroundSignLinesShouldReturnIt )
    {
        test = "&";

        std::istringstream stream( test );
        Lexer lexer( stream );
        Token token( lexer.getNextToken() );
        BOOST_CHECK( token.getType() == TokenType::Background );
    }

    BOOST_AUTO_TEST_CASE( GivenStreamWithReturnDirCommandShouldReturnIt )
    {
        test = "..";

        std::istringstream stream( test );
        Lexer lexer( stream );
        Token token( lexer.getNextToken() );
        BOOST_CHECK( token.getType() == TokenType::CD_Back );
    }

    BOOST_AUTO_TEST_CASE( GivenStreamWithDotNotValidCommandShouldThrowLexerException )
    {
        test = ".,";

        std::istringstream stream( test );
        Lexer lexer( stream );
        BOOST_CHECK_THROW( lexer.getNextToken(), LexerException );
    }

    BOOST_AUTO_TEST_CASE( GivenStreamWithProgCallCommandShouldReturnIt )
    {
        test = "./test";

        std::istringstream stream( test );
        Lexer lexer( stream );
        Token token( lexer.getNextToken() );
        BOOST_CHECK( token.getType() == TokenType::ProgramExecution );
        BOOST_CHECK_EQUAL( token.getValue(), "test" );
    }

    BOOST_AUTO_TEST_CASE( GivenStreamWithSemicolonShouldReturnIt )
    {
        test = ";";

        std::istringstream stream( test );
        Lexer lexer( stream );
        Token token( lexer.getNextToken() );
        BOOST_CHECK( token.getType() == TokenType::Semicolon );
    }

    BOOST_AUTO_TEST_CASE( GivenStreamWithInRedirectShouldReturnIt )
    {
        test = "<";

        std::istringstream stream( test );
        Lexer lexer( stream );
        Token token( lexer.getNextToken() );
        BOOST_CHECK( token.getType() == TokenType::IN_Redirect );
    }

    BOOST_AUTO_TEST_CASE( GivenStreamWithHereDocumentShouldReturnIt )
    {
        test = "<<";

        std::istringstream stream( test );
        Lexer lexer( stream );
        Token token( lexer.getNextToken() );
        BOOST_CHECK( token.getType() == TokenType::HereDocument );
    }

    BOOST_AUTO_TEST_CASE( GivenStreamWithOutRedirectShouldReturnIt )
    {
        test = ">";

        std::istringstream stream( test );
        Lexer lexer( stream );
        Token token( lexer.getNextToken() );
        BOOST_CHECK( token.getType() == TokenType::OUT_Redirect );
    }

    BOOST_AUTO_TEST_CASE( GivenStreamWithErrRedirectShouldReturnIt )
    {
        test = ">>";

        std::istringstream stream( test );
        Lexer lexer( stream );
        Token token( lexer.getNextToken() );
        BOOST_CHECK( token.getType() == TokenType::ERR_Redirect );
    }

    BOOST_AUTO_TEST_CASE( GivenStreamWithAssignmentCharShouldReturnIt )
    {
        test = "=";

        std::istringstream stream( test );
        Lexer lexer( stream );
        Token token( lexer.getNextToken() );
        BOOST_CHECK( token.getType() == TokenType::Assignment );
    }

    BOOST_AUTO_TEST_CASE( GivenStreamWithPipelineCharShouldReturnIt )
    {
        test = "|";

        std::istringstream stream( test );
        Lexer lexer( stream );
        Token token( lexer.getNextToken() );
        BOOST_CHECK( token.getType() == TokenType::Pipeline );
    }

    BOOST_AUTO_TEST_CASE( GivenStreamWithArg1ShouldReturnIt )
    {
        test = "unix.txt_123";

        std::istringstream stream( test );
        Lexer lexer( stream );
        Token token( lexer.getNextToken() );
        BOOST_CHECK( token.getType() == TokenType::Argument );
        BOOST_CHECK_EQUAL( token.getValue(), "unix.txt_123" );
    }

    BOOST_AUTO_TEST_CASE( GivenStreamWithArg2ShouldReturnIt )
    {
        test = "/home/daniel";

        std::istringstream stream( test );
        Lexer lexer( stream );
        Token token( lexer.getNextToken() );
        BOOST_CHECK( token.getType() == TokenType::Argument );
        BOOST_CHECK_EQUAL( token.getValue(), "/home/daniel" );
    }

    BOOST_AUTO_TEST_CASE( GivenStreamWithArg3ShouldReturnIt )
    {
        test = "123_test/aaa.aaa";

        std::istringstream stream( test );
        Lexer lexer( stream );
        Token token( lexer.getNextToken() );
        BOOST_CHECK( token.getType() == TokenType::Argument );
        BOOST_CHECK_EQUAL( token.getValue(), "123_test/aaa.aaa" );
    }

    BOOST_AUTO_TEST_CASE( GivenStreamWithSingleQuoteArgShouldReturnIt )
    {
        test = R"('test\'123\'abc')";

        std::istringstream stream( test );
        Lexer lexer( stream );
        Token token( lexer.getNextToken() );
        BOOST_CHECK( token.getType() == TokenType::SingleQuoteArg );
        BOOST_CHECK_EQUAL( token.getValue(), "test'123'abc" );
    }

    BOOST_AUTO_TEST_CASE( GivenStreamWithSingleQuoteArgWithoutClosingShouldThrowException )
    {
        test = R"('test\'123\'abc)";

        std::istringstream stream( test );
        Lexer lexer( stream );
        BOOST_CHECK_THROW( lexer.getNextToken(), LexerException );
    }

    BOOST_AUTO_TEST_CASE( GivenStreamWithDoubleQuoteArgShouldReturnIt )
    {
        test = R"("test\"123\"abc")";

        std::istringstream stream( test );
        Lexer lexer( stream );
        Token token( lexer.getNextToken() );
        BOOST_CHECK( token.getType() == TokenType::DoubleQuoteArg );
        BOOST_CHECK_EQUAL( token.getValue(), "test\"123\"abc" );
    }

    BOOST_AUTO_TEST_CASE( GivenStreamWithDoubleQuoteArgWithoutClosingShouldThrowException )
    {
        test = R"("test\"123\"abc)";

        std::istringstream stream( test );
        Lexer lexer( stream );
        BOOST_CHECK_THROW( lexer.getNextToken(), LexerException );
    }

    BOOST_AUTO_TEST_CASE( GivenStreamWithFlagShouldReturnIt )
    {
        test = "-c";

        std::istringstream stream( test );
        Lexer lexer( stream );
        Token token( lexer.getNextToken() );
        BOOST_CHECK( token.getType() == TokenType::Flag );
        BOOST_CHECK_EQUAL( token.getValue(), "c" );
    }

    BOOST_AUTO_TEST_CASE( GivenStreamWithInvalidFlagShouldThrowException )
    {
        test = "-_";

        std::istringstream stream( test );
        Lexer lexer( stream );
        BOOST_CHECK_THROW( lexer.getNextToken(), LexerException  );
    }

    BOOST_AUTO_TEST_CASE( GivenStreamWithBashCommandShouldReturnIt )
    {
        test = ",/ls";

        std::istringstream stream( test );
        Lexer lexer( stream );
        Token token( lexer.getNextToken() );
        BOOST_CHECK( token.getType() == TokenType::ShellCommand );
        BOOST_CHECK_EQUAL( token.getValue(), "ls" );
    }

    BOOST_AUTO_TEST_CASE( GitExamlpe1 )
    {
        test = "./program_name arg1 arg2 > out >> err < in;";

        std::istringstream stream( test );
        Lexer lexer( stream );

        std::vector< std::pair< TokenType , std::string > > expected_tokens;
        expected_tokens.emplace_back( TokenType::ProgramExecution, "program_name" );
        expected_tokens.emplace_back( TokenType::Argument, "arg1" );
        expected_tokens.emplace_back( TokenType::Argument, "arg2" );
        expected_tokens.emplace_back( TokenType::OUT_Redirect, "" );
        expected_tokens.emplace_back( TokenType::Argument, "out" );
        expected_tokens.emplace_back( TokenType::ERR_Redirect, "" );
        expected_tokens.emplace_back( TokenType::Argument, "err" );
        expected_tokens.emplace_back( TokenType::IN_Redirect, "" );
        expected_tokens.emplace_back( TokenType::Argument, "in" );
        expected_tokens.emplace_back( TokenType::Semicolon, "" );
        expected_tokens.emplace_back( TokenType::EoF, "" );

        for( auto &token : expected_tokens )
        {
            Token t( lexer.getNextToken() );
            BOOST_CHECK( t.getType() == token.first );
            BOOST_CHECK_EQUAL( t.getValue(), token.second );
        }
    }

    BOOST_AUTO_TEST_CASE( GitExamlpe2 )
    {
        test = "./proga | ./progb | ./progc &";

        std::istringstream stream( test );
        Lexer lexer( stream );
        std::vector< std::pair< TokenType , std::string > > expected_tokens;
        expected_tokens.emplace_back( TokenType::ProgramExecution, "proga" );
        expected_tokens.emplace_back( TokenType::Pipeline, "" );
        expected_tokens.emplace_back( TokenType::ProgramExecution, "progb" );
        expected_tokens.emplace_back( TokenType::Pipeline, "" );
        expected_tokens.emplace_back( TokenType::ProgramExecution, "progc" );
        expected_tokens.emplace_back( TokenType::Background, "" );

        for( auto &token : expected_tokens )
        {
            Token t( lexer.getNextToken() );
            BOOST_CHECK( t.getType() == token.first );
            BOOST_CHECK_EQUAL( t.getValue(), token.second );
        }
    }

BOOST_AUTO_TEST_SUITE_END()