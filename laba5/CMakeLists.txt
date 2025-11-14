cmake_minimum_required(VERSION 3.10)
project(laba5)

set(CMAKE_CXX_STANDARD 17)

find_package(GTest REQUIRED)

include_directories(include)

add_executable(lab5_main 
    src/main.cpp 
    src/block_tracking_memory_resource.cpp
)

add_executable(lab5_test 
    tests/test_dynamic_array.cpp
    tests/test_main.cpp
    src/block_tracking_memory_resource.cpp
)

target_link_libraries(lab5_test GTest::gtest GTest::gtest_main)