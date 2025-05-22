cmake_minimum_required(VERSION 3.31)
project(Practica2)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)
include_directories(cpp)
include_directories(h)

add_executable(Practica2
        cpp/cola.cpp
        cpp/lista.cpp
        cpp/main.cpp
        cpp/Servidor.cpp
        cpp/GestorServidores.cpp
        h/cola.h
        h/lista.h
        h/Servidor.h
        cabeceras.h
        Declaraciones.h)
