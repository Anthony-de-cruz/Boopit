cmake_minimum_required(VERSION 3.27)
project(EmbeddedCWGameCode C)

set(CMAKE_C_STANDARD 99)

add_executable(EmeddedCWGameCode 
        src/main.c
        src/Game.h
        src/Game.c)
