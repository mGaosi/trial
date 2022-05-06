cmake_minimum_required(VERSION 3.9)

set(PROJECT_NAME cpp)
project(${PROJECT_NAME})

set(CMAKE_CXX_STANDARD 17) #-stdc++17
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

message(STATUS "Configure project[${PROJECT_NAME}]: ${CMAKE_CURRENT_SOURCE_DIR}")

list(APPEND SRC_FILES)

macro(add_sub_project project)
    add_executable(${project} "${project}.cpp")
    set_property(TARGET ${project} PROPERTY FOLDER "languages/cpp")
    list(APPEND SRC_FILES "${project}.cpp")
endmacro()

add_sub_project(dynamic_cast)

add_sub_project(function_hiding)

add_sub_project(function_overloading)

add_sub_project(function_overriding)

add_sub_project(friendly)

add_sub_project(value_reference)

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${SRC_FILES})