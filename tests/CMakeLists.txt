

add_subdirectory(shell/ui)
add_subdirectory(shell/tasks)
add_subdirectory(shell/command_parser)
add_subdirectory(shell/model)


file(GLOB_RECURSE TEST_SOURCES "*.cpp")

add_executable(all_unit_tests ${TEST_SOURCES})

target_include_directories(all_unit_tests PRIVATE ${Boost_INCLUDE_DIRS})
target_link_libraries(all_unit_tests ${Boost_LIBRARIES} parser)

