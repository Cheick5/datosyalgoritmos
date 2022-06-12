cmake_minimum_required(VERSION 3.22)
project(Tarea_4 C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(Tarea_4
        arbol_AVL.c
        arbol_AVL.h
        enemigo.h
        main.c)
