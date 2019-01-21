cmake_minimum_required(VERSION 3.12.3)
project(matam_3/wet_files)


set(SOURCE_FILES wet_files/Complex.h
        wet_files/test.cpp
        )


set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -pedantic-errors -Werror -DNDEBUG")

add_executable(matam_3 ${SOURCE_FILES})

