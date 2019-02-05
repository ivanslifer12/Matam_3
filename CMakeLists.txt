cmake_minimum_required(VERSION 3.12.3)
project(matam_3/wet_files)


set(SOURCE_FILES
        wet_files/MtmExceptions.h
        wet_files/Auxilaries.h
        wet_files/Complex.h
        wet_files/Complex.cpp
        wet_files/MtmVec.h
        wet_files/MtmMat.h
        #wet_files/MtmMat.cpp
        wet_files/MtmMatSq.h
        wet_files/MtmMatTriag.h
        #wet_files/main.cpp
        wet_files/Complex.cpp)
#
# wet_files/test.cpp
#
# wet_files/main.cpp
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pedantic-errors  -Wall -Werror -DNDEBUG -std=c++11") #

add_executable(matam_3 ${SOURCE_FILES})