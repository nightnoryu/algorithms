cmake_minimum_required(VERSION 3.8 FATAL_ERROR)

project(heaviestroad VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

set(SOURCES
    src/main.cpp
    src/Args.cpp
    src/GraphParser.cpp
    src/MaxWeightFinder.cpp)
add_executable(${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME} PRIVATE ${PROJECT_SOURCE_DIR}/include)
