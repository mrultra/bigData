cmake_minimum_required(VERSION 3.8)
project(bigData)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp MyDynamicArray.hpp DynamicArray.hpp)
add_executable(bigData ${SOURCE_FILES})