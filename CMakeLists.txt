cmake_minimum_required(VERSION 3.7)
project(
    feader 
    VERSION 0.1.0 
    DESCRIPTION "The C library for Feader"
    )
set(CMAKE_C_FLAGS, "-g -Wall")
add_executable(
    feader-cli 
    src/feader.c
    )
add_library(
    feader SHARED
    src/feader.c
    )
set_target_properties(
    feader
    PROPERTIES 
    VERSION ${PROJECT_VERSION}
    SOVERSION 0
    )
