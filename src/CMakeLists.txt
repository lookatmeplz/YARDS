cmake_minimum_required(VERSION 3.14)
project(YARD)

# Set Source file
set(SOURCE_FILES main.cpp)

# Add Sub Directory (Source Files)
add_subdirectory(base)

# Add Executable SOURCE FILE
add_executable(yards ${SOURCE_FILES})

# Link libraries
target_link_libraries(
        yards
        data_int
        dict
)
