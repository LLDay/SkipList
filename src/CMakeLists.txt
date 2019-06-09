cmake_minimum_required(VERSION 3.0)

add_library(skip_list STATIC skip_list.c)

set_target_properties(skip_list PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/lib)

target_include_directories(skip_list PUBLIC ${PROJECT_SOURCE_DIR}/include)