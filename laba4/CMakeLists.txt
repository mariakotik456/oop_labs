cmake_minimum_required(VERSION 3.10)
project(laba4)

set(CMAKE_CXX_STANDARD 17)

# Поиск пакетов
find_package(GTest REQUIRED)

# Включение директорий
include_directories(include)

# Основная программа
add_executable(lab4_main src/main.cpp)

# Тесты
add_executable(lab4_test 
    tests/test_main.cpp 
    tests/test_figures.cpp
)

# ДОБАВИТЬ ЭТУ СТРОКУ - линковка с GTest
target_link_libraries(lab4_test GTest::gtest GTest::gtest_main)

# Если выше не работает, попробуйте:
# target_link_libraries(lab4_test gtest gtest_main pthread)