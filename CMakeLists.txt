cmake_minimum_required(VERSION 3.7)
project(
    feader 
    )
add_executable(
    feader-cli 
    src/feader.c
    )
add_library(
    feader SHARED
    src/feader.c
    )
