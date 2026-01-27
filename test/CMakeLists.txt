cmake_minimum_required(VERSION 3.20)
project(baybayin)

find_package(GTest REQUIRED)

enable_testing()
add_executable(unit_tests test_baybayin.cpp)
target_include_directories(unit_tests PRIVATE ../include)
target_link_libraries(unit_tests PRIVATE GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(unit_tests)