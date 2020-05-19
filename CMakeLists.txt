cmake_minimum_required(VERSION 3.9)
project(splc)
add_definitions(-std=c++11)

include_directories(${INC_DIR})
link_directories(${LINK_DIR})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-unused-command-line-argument -Wno-deprecated-register")

add_executable(splc main.cpp Ast.h SPL_common.h Ast.cpp parser.cpp parser.hpp lexer.cpp)

