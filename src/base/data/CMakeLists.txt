cmake_minimum_required(VERSION 3.4)
project(data)

# Add Subdirectory atomic
add_subdirectory(atomic)

# Add Library
add_library(data_pack STATIC
        data_int.cpp
        data_boolean.cpp
        data_float.cpp
        data_string.cpp
        data_type.cpp
)
