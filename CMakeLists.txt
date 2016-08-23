cmake_minimum_required(VERSION 3.5)
project(CISP310A1)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp)
add_executable(CISP310A1 ${SOURCE_FILES})