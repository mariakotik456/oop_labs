cmake_minimum_required(VERSION 3.10)
project(laba1)

set(CMAKE_CXX_STANDARD 14)

find_package(GTest REQUIRED)
find_package(Threads REQUIRED)

add_executable(laba1 src/main.cpp src/string_utils.cpp)
target_include_directories(laba1 PRIVATE include)

add_executable(laba1_test test/test_main.cpp test/test_string_utils.cpp src/string_utils.cpp)
target_include_directories(laba1_test PRIVATE include)
target_link_libraries(laba1_test GTest::gtest_main Threads::Threads)