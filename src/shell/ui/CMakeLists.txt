
file(GLOB_RECURSE SOURCES "*.cpp")

add_library(controller ${SOURCES})

target_link_libraries(controller parser model tasks)

