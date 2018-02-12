cmake_minimum_required(VERSION 3.7)
project(Feader)
set(PROJECT_SOURCE_DIR, "src")
include_directories(
	"include"
	"lib"
)
add_executable(Feader src/feader.c)