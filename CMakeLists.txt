cmake_minimum_required(VERSION 4.1)
project(tp5inf3105)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(tp5inf3105
        graphe.h
        main.cpp
        terrain.cpp
        terrain.h)
