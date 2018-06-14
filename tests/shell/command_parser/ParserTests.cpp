//
// Created by Daniel Bigos on 09.06.18.
//

#include <boost/test/unit_test_suite.hpp>
#include <shell/command_parser/Parser.hpp>
#include <shell/command_parser/Lexer.h>
#include <shell/command_parser/structures/Pipeline.h>
#include <boost/test/test_tools.hpp>

BOOST_AUTO_TEST_SUITE( ParserTests )
    using namespace shell::parser;
    using namespace shell::parser::structures;

    std::string test;
    Parser parser;

    BOOST_AUTO_TEST_CASE( GivenEmptyStreamShouldReturnEmptySyntaxTree )
    {
        test = "\n";

        auto syntax_tree = parser.buildTree( test );
        BOOST_REQUIRE( !syntax_tree );
    }

    BOOST_AUTO_TEST_CASE( GivenStreamWithProgramCallShouldReturnIt )
    {
        test = "./test";

        auto syntax_tree = parser.buildTree( test );
        BOOST_REQUIRE( syntax_tree );
        Pipeline *pipeline;
        BOOST_CHECK( pipeline = dynamic_cast< Pipeline* >( syntax_tree.get() ) );
        BOOST_REQUIRE( pipeline->getCommandsList().size() == 1 );
        BOOST_REQUIRE( pipeline->getCommandsList().at( 0 )->getCommands().size() == 1 );
        BOOST_CHECK( pipeline->getCommandsList().at( 0 )->getCommands().at( 0 )->getWord() == "./test" );
    }

    BOOST_AUTO_TEST_CASE( GivenStreamWithProgramCall1ShouldReturnIt )
    {
        test = "./test -c 1 -p test.txt & 1>> out 2> err < in";

        auto syntax_tree = parser.buildTree( test );
        BOOST_REQUIRE( syntax_tree );
        Pipeline *pipeline;
        BOOST_CHECK( pipeline = dynamic_cast< Pipeline* >( syntax_tree.get() ) );
        BOOST_REQUIRE( pipeline->getCommandsList().size() == 1 );
        BOOST_REQUIRE( pipeline->getCommandsList().at( 0 )->getCommands().size() == 1 );
        BOOST_CHECK( pipeline->getCommandsList().at( 0 )->getCommands().at( 0 )->getWord() == "./test" );
        BOOST_REQUIRE( pipeline->getCommandsList().at( 0 )->getCommands().at( 0 )->getArguments().size() == 4 );
        BOOST_CHECK( pipeline->getCommandsList().at( 0 )->getCommands().at( 0 )->getArguments().at( 0 ) == "-c" );
        BOOST_CHECK( pipeline->getCommandsList().at( 0 )->getCommands().at( 0 )->getArguments().at( 1 ) == "1" );
        BOOST_CHECK( pipeline->getCommandsList().at( 0 )->getCommands().at( 0 )->getArguments().at( 2 ) == "-p" );
        BOOST_CHECK( pipeline->getCommandsList().at( 0 )->getCommands().at( 0 )->getArguments().at( 3 ) == "test.txt" );
        BOOST_CHECK( pipeline->getCommandsList().at( 0 )->getCommands().at( 0 )->getIsBackground() );
        BOOST_REQUIRE( pipeline->getCommandsList().at( 0 )->getCommands().at( 0 )->getRedirections().size() == 3 );
        OutAppend *append;
        ErrRedirection *err;
        InRedirection *in;
        BOOST_CHECK( append = dynamic_cast< OutAppend * >( pipeline->getCommandsList().at( 0 )->getCommands().at( 0 )->getRedirections().at( 0 ).get() ) );
        BOOST_CHECK( err = dynamic_cast< ErrRedirection * >( pipeline->getCommandsList().at( 0 )->getCommands().at( 0 )->getRedirections().at( 1 ).get() ) );
        BOOST_CHECK( in = dynamic_cast< InRedirection * >( pipeline->getCommandsList().at( 0 )->getCommands().at( 0 )->getRedirections().at( 2 ).get() ) );
        BOOST_CHECK( pipeline->getCommandsList().at( 0 )->getCommands().at( 0 )->getRedirections().at( 0 )->getPath() == "out" );
        BOOST_CHECK( pipeline->getCommandsList().at( 0 )->getCommands().at( 0 )->getRedirections().at( 1 )->getPath() == "err" );
        BOOST_CHECK( pipeline->getCommandsList().at( 0 )->getCommands().at( 0 )->getRedirections().at( 2 )->getPath() == "in" );
    }

    BOOST_AUTO_TEST_CASE( GivenStreamWithPipelineShouldReturnIt )
    {
        test = "./proga | ./progb | ./progc";

        auto syntax_tree = parser.buildTree( test );
        BOOST_REQUIRE( syntax_tree );
        Pipeline *pipeline;
        BOOST_CHECK( pipeline = dynamic_cast< Pipeline* >( syntax_tree.get() ) );
        BOOST_REQUIRE( pipeline->getCommandsList().size() == 3 );
    }

    BOOST_AUTO_TEST_CASE( GivenStreamWithAssignmentShouldReturnIt )
    {
        test = "VAR= TEST";

        auto syntax_tree = parser.buildTree( test );
        BOOST_REQUIRE( syntax_tree );
        Assignment *assignment;
        BOOST_CHECK( assignment = dynamic_cast< Assignment* >( syntax_tree.get() ) );
        BOOST_CHECK_EQUAL( assignment->getVariable(), "VAR" );
        BOOST_CHECK_EQUAL( assignment->getValue(), "TEST" );
    }

    BOOST_AUTO_TEST_CASE( GivenStreamWithAssignmentToEnvVarShouldReturnIt )
    {
        test = "VAR= $TEST";

        auto syntax_tree = parser.buildTree( test );
        BOOST_REQUIRE( syntax_tree );
        Assignment *assignment;
        BOOST_CHECK( assignment = dynamic_cast< Assignment* >( syntax_tree.get() ) );
        BOOST_CHECK_EQUAL( assignment->getVariable(), "VAR" );
        BOOST_CHECK_EQUAL( assignment->getValue(), "" );
    }

    BOOST_AUTO_TEST_CASE( GivenStreamWithAssignmentToSingleQuoteShouldReturnIt )
    {
        test = "VAR= 'TEST'";

        auto syntax_tree = parser.buildTree( test );
        BOOST_REQUIRE( syntax_tree );
        Assignment *assignment;
        BOOST_CHECK( assignment = dynamic_cast< Assignment* >( syntax_tree.get() ) );
        BOOST_CHECK_EQUAL( assignment->getVariable(), "VAR" );
        BOOST_CHECK_EQUAL( assignment->getValue(), "TEST" );
    }

    BOOST_AUTO_TEST_CASE( GivenStreamWithAssignmentToDoubleQuoteShouldReturnIt )
    {
        test = "VAR= \"$TEST 1 $ABC\"";

        auto syntax_tree = parser.buildTree( test );
        BOOST_REQUIRE( syntax_tree );
        Assignment *assignment;
        BOOST_CHECK( assignment = dynamic_cast< Assignment* >( syntax_tree.get() ) );
        BOOST_CHECK_EQUAL( assignment->getVariable(), "VAR" );
        BOOST_CHECK_EQUAL( assignment->getValue(), " 1 " );
    }
BOOST_AUTO_TEST_SUITE_END()

