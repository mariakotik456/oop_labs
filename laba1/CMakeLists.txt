cmake_minimum_required(VERSION 3.10)
project(laba1)

set(CMAKE_CXX_STANDARD 14)

add_executable(laba1 src/main.cpp src/string_utils.cpp)

target_include_directories(laba1 PRIVATE include)