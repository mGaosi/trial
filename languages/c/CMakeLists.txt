cmake_minimum_required(VERSION 3.9)

set(PROJECT_NAME c)
project(${PROJECT_NAME})

set(CMAKE_C_STANDARD 11) #-stdc17 gnuc11
set(CMAKE_C_STANDARD_REQUIRED ON)

message(STATUS "Configure project[${PROJECT_NAME}]: ${CMAKE_CURRENT_SOURCE_DIR}")

list(APPEND SRC_FILES)

macro(add_sub_project project)
    add_executable(${project} "${project}.c")
    set_property(TARGET ${project} PROPERTY FOLDER "languages/c")
    list(APPEND SRC_FILES "${project}.c")
endmacro()

add_sub_project(sizeof)

add_sub_project(zero_length_array)

add_sub_project(alignment)

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${SRC_FILES})
