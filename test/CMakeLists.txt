cmake_minimum_required(VERSION 3.20)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
project(baybayin)

find_package(GTest REQUIRED)

enable_testing()
add_executable(unit_tests unit_tests.cpp
        unit_tests.h)
target_include_directories(unit_tests PRIVATE ../include)
target_link_libraries(unit_tests PRIVATE GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(unit_tests)