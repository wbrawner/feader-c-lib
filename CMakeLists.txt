cmake_minimum_required(VERSION 3.5)
project(
    feader 
    )
add_library(
    feader STATIC
    src/feader.c
    )
add_library(
    sqlite3 STATIC
    src/sqlite/sqlite3.c
    )
add_library(
    yxml STATIC
    src/yxml/yxml.c
    )
target_link_libraries(
    feader
    sqlite3
    yxml
)