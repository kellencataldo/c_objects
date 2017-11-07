cmake_minimum_required(VERSION 3.8)
project(c_objects)

set(CMAKE_C_STANDARD 11)

set(INCLUDE ./lib/include)
set(TEST ./test/)
set(SRC ./lib/src)

include_directories(${INCLUDE} ${TEST})


link_directories(${INCLUDE} ${TEST})

set(SOURCE_FILES main.c lib/include/list_functions.h lib/src/list_functions.c test/test_1.c test/test.h)
add_executable(c_objects ${SOURCE_FILES})