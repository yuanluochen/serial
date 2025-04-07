cmake_minimum_required(VERSION 3.10.0)
project(serial VERSION 0.1.0 LANGUAGES C CXX)
include_directories(include)
file(GLOB SRC_LIST "main.c" "app/*.*" "hardware/*.*")
add_executable(serial ${SRC_LIST})

