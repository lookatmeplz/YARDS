cmake_minimum_required(VERSION 3.4)
project(db)

# Add Library
add_library(db
        db.cpp
)

target_link_libraries(
        db
        atomic
        data_pack
        struct
)
