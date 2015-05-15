cmake_minimum_required(VERSION 3.2)
project(Remote)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -g -Werror")

set(SOURCE_FILES
    client.c
    common.c
    iv_remote.h
    iv_standard.c
    iv_standard.h
    main.c
    server.c)
add_library(../Determinant/ivmatrix.o)

add_executable(remoted ${SOURCE_FILES})
target_link_libraries(remoted pthread)