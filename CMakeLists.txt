cmake_minimum_required(VERSION 3.10)
project(uxp1a_shell)

set(CMAKE_CXX_STANDARD 17)

find_package(Boost 1.60 REQUIRED COMPONENTS unit_test_framework)

include_directories(src/)
include_directories(${Boost_INCLUDE_DIRS})


add_subdirectory(src/)
add_subdirectory(tests/)
