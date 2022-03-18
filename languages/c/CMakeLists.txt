cmake_minimum_required(VERSION 3.9)

set(PROJECT_NAME c)
project(${PROJECT_NAME})

set(CMAKE_C_STANDARD 11) #-stdc17 gnuc11
set(CMAKE_C_STANDARD_REQUIRED ON)

message(STATUS "Configure project[${PROJECT_NAME}]: ${CMAKE_CURRENT_SOURCE_DIR}")

add_executable(sizeof sizeof.c)
set_property(TARGET sizeof PROPERTY FOLDER "languages/c")

add_executable(zero_length_array zero_length_array.c)
set_property(TARGET zero_length_array PROPERTY FOLDER "languages/c")
