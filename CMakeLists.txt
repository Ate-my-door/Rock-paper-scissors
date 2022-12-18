cmake_minimum_required(VERSION 3.10)

project(Rock-Paper-Scissors CXX)

add_executable(rock rock.cpp)

add_compile_options(rock PUBLIC -Wall)
