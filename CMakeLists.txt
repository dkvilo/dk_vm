cmake_minimum_required(VERSION 3.20)
project(dk_vm)

set(CMAKE_C_STANDARD 11)
set(CMAKE_COMPILER_IS_GNUCC TRUE)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS}")

set(SOURCE_FILES ./vm/main.c)
add_executable(dk_vm ${SOURCE_FILES})
