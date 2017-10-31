cmake_minimum_required(VERSION 3.1)
cmake_policy(VERSION 3.1)
cmake_policy(SET CMP0037 NEW)

project(eopi C CXX)

# general compile options
add_compile_options(${CMAKE_CXX_FLAGS} -std=c++14)
add_compile_options(${CMAKE_CXX_FLAGS} -W)
add_compile_options(${CMAKE_CXX_FLAGS} -Wall)
add_compile_options(${CMAKE_CXX_FLAGS} -Wextra)
add_compile_options(${CMAKE_CXX_FLAGS} -Wuninitialized)
add_compile_options(${CMAKE_CXX_FLAGS} -Wreturn-type)
add_compile_options(${CMAKE_CXX_FLAGS} -Wunreachable-code)
add_compile_options(${CMAKE_CXX_FLAGS} -Wstrict-overflow=2)
add_compile_options(${CMAKE_CXX_FLAGS} -pedantic)

set(CMAKE_EXPORT_COMPILE_COMMANDS 1)
include_directories(.)

# testing
enable_testing()
add_subdirectory(test)
