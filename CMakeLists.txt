cmake_minimum_required(VERSION 3.21)
project(paralleltask4)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++20 -fopenmp")

add_executable(paralleltask4 main.cpp)
