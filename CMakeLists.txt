cmake_minimum_required(VERSION 3.9)
project(splc)
add_definitions(-std=c++11)

execute_process(COMMAND llvm-config --libdir OUTPUT_VARIABLE LLVM_LINK_DIR)
string(REGEX REPLACE "\n$" "" LLVM_LINK_DIR "${LLVM_LINK_DIR}")
set(LINK_DIR ${LINK_DIR} ${LLVM_LINK_DIR})
execute_process(COMMAND llvm-config --libnames OUTPUT_VARIABLE LLVM_LIB)
string(REGEX REPLACE "\n$" "" LLVM_LIB "${LLVM_LIB}")
include_directories(${INC_DIR})
link_directories(${LINK_DIR})
message(${LINK_DIR})
message(${LLVM_LIB})

# execute_process(COMMAND llvm-config --cxxflags --ldflags --system-libs --libs core OUTPUT_VARIABLE FLAGS)
# message(${CMAKE_CXX_FLAGS})

add_executable(splc main.cpp Ast.h SPL_common.h Ast.cpp parser.cpp parser.hpp lexer.cpp CodeGen.cpp SymbolTable.cpp SystemFunc.cpp)
target_link_libraries(splc ${LLVM_LIB})