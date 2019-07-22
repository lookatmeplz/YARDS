cmake_minimum_required(VERSION 3.14)
project(data)

# Add Library
add_library(data_pack data_int.cpp data_boolean.cpp data_boolean.h data_float.cpp data_float.h data_string.cpp data_string.h)
