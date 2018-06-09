
add_subdirectory(shell/model)
add_subdirectory(shell/command_parser)
add_subdirectory(shell/tasks)
add_subdirectory(shell/ui)

add_executable(uxp1a_shell main.cpp)
target_link_libraries(uxp1a_shell model parser)