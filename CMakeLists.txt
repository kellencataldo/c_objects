cmake_minimum_required(VERSION 3.8)
project(c_objects)

set(CMAKE_C_STANDARD 11)

set(INCLUDE ./lib/include)
set(TEST ./test/)
set(SRC ./lib/src)

include_directories(${INCLUDE} ${TEST})


link_directories(${INCLUDE} ${TEST})

set(SOURCE_FILES
        main.c
        lib/include/list_functions.h
        lib/src/list_functions.c
        test/test_0.c test/test.h
        lib/src/string_class.c
        lib/include/string_class.h
        test/test_1.c lib/include/class.h
        test/test_2.c
        lib/src/class.c)
set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin")
add_executable(c_objects ${SOURCE_FILES})