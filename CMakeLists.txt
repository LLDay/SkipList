cmake_minimum_required(VERSION 3.0)

project(skip_list C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -pedantic -Wall -Wextra")

add_subdirectory(src src)
add_subdirectory(test test)