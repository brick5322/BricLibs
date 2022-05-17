cmake_minimum_required(VERSION 3.22)
project(BricLibs)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(ex_Spliter
        examples/ex_Spliter.cpp
        List.c
        List.h
        Node.c
        Node.h
        pubdefs.h
        Spliter.cpp
        Spliter.h)

add_executable(ex_List_cstr
        examples/ex_List_cstr.cpp
        List.c
        List.h
        List_cstr.cpp
        List_cstr.h
        Node.c
        Node.h
        pubdefs.h
)
