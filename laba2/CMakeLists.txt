cmake_minimum_required(VERSION 3.10)
project(laba2)

set(CMAKE_CXX_STANDARD 14)

find_package(GTest REQUIRED)
find_package(Threads REQUIRED)

add_executable(lab2_main src/main.cpp src/quinary_integer.cpp)
target_include_directories(lab2_main PRIVATE include)

add_executable(lab2_test test/test_main.cpp test/test_quinary_integer.cpp src/quinary_integer.cpp)
target_include_directories(lab2_test PRIVATE include)
target_link_libraries(lab2_test GTest::gtest_main Threads::Threads)