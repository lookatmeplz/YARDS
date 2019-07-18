cmake_minimum_required(VERSION 3.14)
project(base)

# Add Subdirectory (data)
add_subdirectory(data)

# Add Library
add_library(dict dictionary.cpp)
