cmake_minimum_required(VERSION 3.19)
project(Hexxagon C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(Hexxagon
        hexxagon_control.c
        hexxagon_control.h
        hexxagon_graphics.c
        hexxagon_graphics.h
        main.c)
