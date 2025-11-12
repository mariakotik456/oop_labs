cmake_minimum_required(VERSION 3.10)
project(laba4)

set(CMAKE_CXX_STANDARD 17)

find_package(GTest REQUIRED)

include_directories(include)

add_executable(lab4_main src/main.cpp)

add_executable(lab4_test 
    tests/test_main.cpp 
    tests/test_figures.cpp
)

target_link_libraries(lab4_test GTest::gtest GTest::gtest_main)
