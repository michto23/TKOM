cmake_minimum_required(VERSION 2.8)
project(TKOM)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

find_package(FLEX)
include_directories(${CMAKE_CURRENT_BINARY_DIR})
include_directories(${Project_SOURCE_DIR})

FLEX_TARGET(MyScanner scan.y  ${CMAKE_CURRENT_BINARY_DIR}/lex.yy.cc COMPILE_FLAGS -+)

set(SOURCE_FILES main.cc token/TokenType.h token/Token.hpp parser/Parser.cpp parser/Parser.h treeObjects/HtmlDocument.hpp treeObjects/Doctype.hpp treeObjects/Component.hpp treeObjects/HtmlAttribute.hpp malwrAnalysis/MalwrAnalyzer.cpp malwrAnalysis/MalwrAnalyzer.h malwrAnalysis/MalwrDTO.h json/json.h json/json-forwards.h jsoncpp.cpp scanner/Scanner.cpp scanner/Scanner.h malwrAnalysis/MalwrDTO.cpp exception/PerrorException.hpp)

add_executable(Analizator
        ${SOURCE_FILES}
        ${FLEX_MyScanner_OUTPUTS}
        )