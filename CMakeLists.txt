cmake_minimum_required(VERSION 3.24)
project(Mach_O)

set(CMAKE_CXX_STANDARD 17)

include_directories(./header)

add_library(SOOURCE STATIC ./src/macho_file.cpp)

add_executable(Mach_O ./main.cpp)

target_link_libraries(Mach_O SOOURCE)
