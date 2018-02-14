cmake_minimum_required(VERSION 3.7)
project(Feader)
set(CMAKE_C_FLAGS, "-g -Wall")
include_directories(
    "/usr/local/include"
    "/usr/include/x86_64-linux-gnu"
    "/usr/local/include/libxml2"
    "include"
)
link_directories(
    "/usr/lib/x86_64-linux-gnu"
    "/usr/local/lib"
    "lib"
)
add_executable(Feader src/feader.c)
find_package(libcurl)
target_link_libraries(
    Feader
    curl
    xml2
    )
