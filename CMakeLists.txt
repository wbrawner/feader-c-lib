cmake_minimum_required(VERSION 3.7)
project(
    feader 
    VERSION 0.1.0 
    DESCRIPTION "The C library for Feader"
    )
set(CMAKE_C_FLAGS, "-g -Wall")
include_directories(
    "/usr/include"
    "/usr/include/libxml2"
    "/usr/include/x86_64-linux-gnu"
    "/data/data/com.termux/files/usr/include"
    "/data/data/com.termux/files/usr/include/libxml2"
    "include"
)
link_directories(
    "/usr/lib/x86_64-linux-gnu"
    "/usr/lib"
    "/data/data/com.termux/files/usr/lib"
    "lib"
)
add_executable(feader-cli src/feader.c)
add_library(
    feader SHARED
    src/feader.c
    )
target_link_libraries(
    feader-cli
    curl
    sqlite3
    xml2
    )
target_link_libraries(
    feader
    curl
    sqlite3
    xml2
    )
set_target_properties(
    feader
    PROPERTIES 
    VERSION ${PROJECT_VERSION}
    SOVERSION 0
    )
