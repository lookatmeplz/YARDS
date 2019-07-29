cmake_minimum_required(VERSION 3.4)
project(atomic)

# Add Library
add_library(atomic STATIC
        atom_boolean.cpp
        atom_float.cpp
        atom_int.cpp
)
