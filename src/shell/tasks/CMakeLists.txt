file(GLOB_RECURSE SOURCES "*.cpp")

add_library(tasks ${SOURCES})
target_link_libraries(tasks ${Boost_LIBRARIES} controller)