
file(GLOB_RECURSE SOURCES "*.cpp")

add_library(model ${SOURCES} domain/variables/Variable.cpp domain/VariableFactory.cpp domain/VariablesRepository.cpp)

