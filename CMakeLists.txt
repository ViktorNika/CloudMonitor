set(project "EFDMonitor")
project(${project})

cmake_minimum_required(VERSION 3.10)

add_definitions(-std=c++11 -O3)
include_directories(include)

file(GLOB SOURCES src/*.cpp)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/public")
add_executable(${project} ${SOURCES})
