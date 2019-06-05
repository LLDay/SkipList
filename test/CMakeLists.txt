cmake_minimum_required(VERSION 3.0)

add_executable(test_e test.c)
add_test(test test_e)

target_link_libraries(test_e skip_list)