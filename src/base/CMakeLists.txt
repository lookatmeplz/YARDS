cmake_minimum_required(VERSION 3.4)
project(base)

# Add Subdirectory (data)
add_subdirectory(data)

# Add Library
add_library(dict
        dictionary.cpp
        node.cpp
)
