cmake_minimum_required(VERSION 3.0)

include_directories(ctest)

add_executable(test test.c)
target_link_libraries(test skip_list)

add_test(NAME test COMMAND test)