cmake_minimum_required(VERSION 3.10)
project(posit_c)

set(CMAKE_CXX_STANDARD 14)

enable_testing()

add_executable(posit_c
        README.md
        src/main.cpp
        src/Posit.cpp)

add_subdirectory(tests)
