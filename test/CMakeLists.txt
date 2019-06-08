cmake_minimum_required(VERSION 3.0)

include_directories(ctest)

set(CTEST_OUTPUT_ON_FAILURE ON)

add_executable(unit_test test.c)
target_link_libraries(unit_test skip_list)

add_test(NAME unit_test COMMAND unit_test)