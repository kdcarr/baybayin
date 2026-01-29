cmake_minimum_required(VERSION 3.20)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
project(baybayin)

find_package(cli11 REQUIRED)

add_executable(bbn main.cpp)
target_include_directories(bbn PRIVATE ../include)
target_link_libraries(bbn PRIVATE CLI11::CLI11)

