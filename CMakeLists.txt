cmake_minimum_required(VERSION 3.7)
project(JohnnyDeppendency)

set(CMAKE_CXX_STANDARD 11)

#Bring the headers, such as Student.h into the project
include_directories(include)

#However, the file(GLOB...) allows for wildcard additions:
file(GLOB SOURCE_FILES "src/*.cpp")

add_executable(JohnnyDeppendency ${SOURCE_FILES})