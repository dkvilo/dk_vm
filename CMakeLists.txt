cmake_minimum_required(VERSION 3.20)
project(dk_lang)

set(CMAKE_C_STANDARD 11)
set(CMAKE_COMPILER_IS_GNUCC TRUE)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS}")

include_directories(vm)
include_directories(lex)

set(SOURCE_FILES vm/vm.c cli/main.c)
add_executable(dk_cli ${SOURCE_FILES})

function(linx_lex_lib)
    if (CMAKE_SYSTEM_NAME MATCHES "Linux")
        target_link_libraries(dk_cli ${CMAKE_SOURCE_DIR}/lex/linux/libdklexer.a)
    elseif(CMAKE_SYSTEM_NAME MATCHES "Darwin")
        target_link_libraries(dk_cli ${CMAKE_SOURCE_DIR}/lex/macos/libdklexer.a)
    elseif (CMAKE_SYSTEM_NAME MATCHES "Windows")
        message(FATAL_ERROR "Lexer library not found. Please build the lexer library and place it in the lex directory.")
    else()
        message(FATAL_ERROR "Unsupported platform")
    endif()
endfunction()

linx_lex_lib()
