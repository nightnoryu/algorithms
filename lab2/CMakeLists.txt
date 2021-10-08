cmake_minimum_required(VERSION 3.8 FATAL_ERROR)

project(dijkstracalc VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

set(SOURCES
  src/InfixToPostfixParser.cpp
  src/ParseLogger.cpp
  src/PostfixCalculator.cpp
  src/main.cpp
)
add_executable(${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME} PRIVATE ${PROJECT_SOURCE_DIR}/src)
