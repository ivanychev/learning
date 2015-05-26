cmake_minimum_required(VERSION 2.8.4)

project(remote_matrix)

set(CMAKE_C_COMPILER             "/usr/bin/clang")
set(CMAKE_C_FLAGS                "${CMAKE_C_FLAGS} -Wall -Werror -g -pthread")


set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/build/")

set(SOURCE_FILES
    include/iv_remote.h
    include/iv_standard.h
    sources/client.c
    sources/common.c
    sources/iv_standard.c
    sources/main.c
    sources/server.c
    sources/ivmatrix.c)

link_directories(${PROJECT_SOURCE_DIR}/../Determinant)
add_executable(remote_matrix ${SOURCE_FILES})
