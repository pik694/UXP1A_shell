file(GLOB_RECURSE TEST_SOURCES "*.cpp")

add_executable(parser_unit_tests  ../../tests_main.cpp ${TEST_SOURCES})

target_include_directories(parser_unit_tests PRIVATE ${Boost_INCLUDE_DIRS})
target_link_libraries(parser_unit_tests ${Boost_LIBRARIES} parser)