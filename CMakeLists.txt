cmake_minimum_required(VERSION 3.24)
project(projet_tla C)

set(CMAKE_C_STANDARD 11)

add_executable(projet_tla main.c Pile.h Pile.c Terminal.h)
