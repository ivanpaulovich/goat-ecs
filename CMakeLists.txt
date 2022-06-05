cmake_minimum_required(VERSION 3.10)
project(Goat)

set(CMAKE_CXX_STANDARD 14)

include_directories(src)

add_subdirectory(src)

enable_testing()
add_subdirectory(test)
