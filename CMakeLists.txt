cmake_minimum_required(VERSION 3.5)
project(TKOM)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cc TokenType.h)
add_executable(TKOM ${SOURCE_FILES})