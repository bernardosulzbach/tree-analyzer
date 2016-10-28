cmake_minimum_required (VERSION 2.8.7)

project (tree-comparison C)

if (("${CMAKE_C_COMPILER_ID}" STREQUAL "Clang") OR ("${CMAKE_C_COMPILER_ID}" STREQUAL "GNU"))
    set (CMAKE_C_FLAGS "-Wall -Wextra -Wpedantic -std=c89")
endif ()

set (CMAKE_EXPORT_COMPILE_COMMANDS 1)

add_executable (tree-comparison src/main.c src/constants.h src/constants.c src/BST.h src/BST.c src/AVL.h src/AVL.c)
