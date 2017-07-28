cmake_minimum_required(VERSION 3.7)
project(JohnnyDeppendency)

set(CMAKE_CXX_STANDARD 11)

#Bring the headers, such as into the project
include_directories(include)

#However, the file(GLOB...) allows for wildcard additions:
file(GLOB SOURCE_FILES "src/*.cpp")

#add_executable(JohnnyDeppendency ${SOURCE_FILES} src/token.cpp include/token.h src/utils.cpp include/utils.h src/oracle.cpp include/oracle.h src/perceptron.cpp include/perceptron.h src/Multiperceptron.cpp include/Multiperceptron.h )
add_executable(JohnnyDeppendency ${SOURCE_FILES})
