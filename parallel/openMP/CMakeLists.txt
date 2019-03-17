cmake_minimum_required(VERSION 3.12)
project(openMP)

set(CMAKE_CXX_STANDARD 17)

find_package(OpenMP)
if (OPENMP_FOUND)
    set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
    set (CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")
endif()

add_executable(openMP1 1.cpp helper.h)
add_executable(openMP2 2.cpp)
add_executable(openMP3 3.cpp)
add_executable(openMP4 4.cpp)
add_executable(openMP5 5.cpp)
add_executable(openMP6 6.cpp)