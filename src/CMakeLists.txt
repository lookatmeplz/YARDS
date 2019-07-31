cmake_minimum_required(VERSION 3.4)
project(YARD)

# Set Source file
set(SOURCE_FILES main.cpp)

# Add Sub Directory (Source Files)
add_subdirectory(base)
add_subdirectory(net)
add_subdirectory(cmd)
add_subdirectory(db)

# Add Executable SOURCE FILE
add_executable(yards ${SOURCE_FILES})

# Link libraries
target_link_libraries(
        yards
        atomic
        data_pack
        struct
        net_server
        net_client
        db
        cmd
)
