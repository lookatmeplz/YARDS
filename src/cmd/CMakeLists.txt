cmake_minimum_required(VERSION 3.4)
project(cmd)

# Add Library
add_library(cmd
        mngr.cpp
        parser.cpp
        user.cpp
)

target_link_libraries(
        cmd
        data_pack
        struct
)
