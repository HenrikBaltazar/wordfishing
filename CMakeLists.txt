cmake_minimum_required(VERSION 4.0)
project(wordfishing)

set(CMAKE_CXX_STANDARD 20)

add_executable(wordfishing main.cpp
        InputFile.cpp
        InputFile.h)
