cmake_minimum_required(VERSION 3.0)

add_library(skip_list skip_list.c)
target_include_directories(skip_list PUBLIC ${PROJECT_SOURCE_DIR}/include)