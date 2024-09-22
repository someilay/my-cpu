cmake_minimum_required(VERSION 3.13)
project(my-cpu C CXX)

option(MY_CPU_BUILD_TESTS "Build tests for my-cpu" OFF)

set(CMAKE_C_STANDARD 99)
set(CXX_STANDARD 14)

add_library(my-cpu SHARED)
target_compile_options(my-cpu PRIVATE -Wall -Wextra -Wpedantic)
target_include_directories(
    my-cpu
    PUBLIC include
    PRIVATE src
)
add_subdirectory(src/basic)
add_subdirectory(src/gates)
add_subdirectory(src/latches)
add_subdirectory(src/arithmetic_units)

if(MY_CPU_BUILD_TESTS)
  add_subdirectory(test)
endif()
