cmake_minimum_required(VERSION 3.4)
project(net)

# Add Library
add_library(net_server
        Server.cpp
        Server.h
)
add_library(net_client
        Client.cpp
        Client.h
)