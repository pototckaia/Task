cmake_minimum_required(VERSION 3.12)
project(openMP)

set(CMAKE_CXX_STANDARD 17)

add_executable(main main.cpp GraphParser.cpp GraphParser.h)
