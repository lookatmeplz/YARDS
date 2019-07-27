cmake_minimum_required(VERSION 3.4)
project(net)

# Add Library
add_library(net_server
        server.cpp
        server.h
)
add_library(net_client
        client.cpp
        client.h
)