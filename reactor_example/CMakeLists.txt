cmake_minimum_required (VERSION 2.8.11)
project(REACTOR_EXAMPLE)

set (CMAKE_CXX_STANDARD 11)
add_definitions(-DENABLE_DEBUG_MACRO)

add_subdirectory (reactor)
add_subdirectory (example)