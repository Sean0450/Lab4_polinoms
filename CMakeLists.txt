cmake_minimum_required(VERSION 3.2)

project(Lab_polinoms)

set(SOURCE_EXE source/Main.cpp)

set(SOURCE_LIB source/Monom.cpp)

set(SOURCE_LIB_2 source/Polinom.cpp)

add_library(Monom ${SOURCE_LIB})

add_library(Polinom ${SOURCE_LIB_2})

add_executable(main ${SOURCE_EXE})

target_link_libraries(main Monom Polinom source/List.h)

