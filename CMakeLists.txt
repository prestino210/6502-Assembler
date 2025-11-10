cmake_minimum_required(VERSION 3.20)

project(R65Assembler C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

include_directories(${CMAKE_SOURCE_DIR}/include)

file(GLOB SOURCES "${CMAKE_SOURCE_DIR}/src/*.c")

add_executable(R65A ${SOURCES})

target_compile_options(R65A PRIVATE -Wall -Wextra -Wpedantic)

add_custom_target(distclean
    COMMAND ${CMAKE_COMMAND} -P ${CMAKE_BINARY_DIR}/cmake_clean.cmake
)

file(WRITE ${CMAKE_BINARY_DIR}/cmake_clean.cmake
"file(REMOVE_RECURSE ${CMAKE_BINARY_DIR}/CMakeFiles
${CMAKE_BINARY_DIR}/CMakeCache.txt
${CMAKE_BINARY_DIR}/Makefile
${CMAKE_BINARY_DIR}/cmake_install.cmake)")
