cmake_minimum_required(VERSION 2.8)
project(TKOM)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

find_package(FLEX)

FLEX_TARGET(MyScanner scan.y  ${CMAKE_CURRENT_BINARY_DIR}/lex.yy.cc COMPILE_FLAGS -+)

set(SOURCE_FILES main.cc TokenType.h)

include_directories(${CMAKE_CURRENT_BINARY_DIR})
include_directories(${Project_SOURCE_DIR})
add_executable(Analizator
        ${SOURCE_FILES}
        ${FLEX_MyScanner_OUTPUTS}
        )