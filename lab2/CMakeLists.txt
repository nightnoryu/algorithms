cmake_minimum_required(VERSION 3.8 FATAL_ERROR)

project(dijkstracalc VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

file(GLOB SOURCES "src/*.cpp" "src/*.h")
add_executable(${PROJECT_NAME} ${SOURCES})
