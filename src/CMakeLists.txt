cmake_minimum_required(VERSION 3.16)

project(src VERSION 1)
set(CMAKE_CXX_STANDARD 14)
add_executable(JSONParser main.cpp JSONNode.h JSONNode.cpp Token.cpp Token.h JSONParser.cpp JSONParser.h)
include_directories(${CMAKE_SOURCE_DIR})
set(CMAKE_BUILD_TYPE Debug)

target_link_libraries(JSONParser PUBLIC g)
