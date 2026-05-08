cmake_minimum_required(VERSION 3.28)
project(untitled CXX)

set(CMAKE_CXX_STANDARD 20)

include_directories(
        ${CMAKE_CURRENT_SOURCE_DIR}/Estructuras
)

add_executable(untitled
        main.cpp
        Estructuras/Reproductor.cpp
        Estructuras/Cancion.cpp
)