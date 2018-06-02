file(GLOB_RECURSE TEST_SOURCES "*.cpp")

add_executable(ui_unit_tests  ../../tests_main.cpp ${TEST_SOURCES})

target_include_directories(ui_unit_tests PRIVATE ${Boost_INCLUDE_DIRS})
target_link_libraries(ui_unit_tests ${Boost_LIBRARIES})