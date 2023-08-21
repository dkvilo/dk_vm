cmake_minimum_required(VERSION 3.20)
project(dk_lang)

set(CMAKE_C_STANDARD 11)
set(CMAKE_COMPILER_IS_GNUCC TRUE)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS}")

include_directories(vm)

set(SOURCE_FILES vm/vm.c cli/main.c)
add_executable(dk_cli ${SOURCE_FILES})
