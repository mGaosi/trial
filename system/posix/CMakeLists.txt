cmake_minimum_required(VERSION 3.9)

set(PROJECT_NAME posix)
project(${PROJECT_NAME})

set(CMAKE_CXX_STANDARD 17) #-stdc++17
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

message(STATUS "Configure project[${PROJECT_NAME}]: ${CMAKE_CURRENT_SOURCE_DIR}")

add_executable(fork fork.cpp)
set_property(TARGET fork PROPERTY FOLDER "system/posix")

add_executable(mmap mmap.cpp)
set_property(TARGET mmap PROPERTY FOLDER "system/posix")
