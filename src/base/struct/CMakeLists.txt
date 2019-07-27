cmake_minimum_required(VERSION 3.4)
project(struct)

# Add Library
add_library(struct STATIC
        list.cpp
        tuple.cpp
        dictionary.cpp
        node.cpp
)
