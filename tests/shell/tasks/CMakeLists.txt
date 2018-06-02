file(GLOB_RECURSE TEST_SOURCES "*.cpp")

add_executable(tasks_unit_tests ../../tests_main.cpp ${TEST_SOURCES})

target_include_directories(tasks_unit_tests PRIVATE ${Boost_INCLUDE_DIRS})
target_link_libraries(tasks_unit_tests ${Boost_LIBRARIES})