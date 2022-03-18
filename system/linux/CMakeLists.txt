cmake_minimum_required(VERSION 3.9)

set(PROJECT_NAME linux)
project(${PROJECT_NAME})

set(CMAKE_CXX_STANDARD 17) #-stdc++17
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

message(STATUS "Configure project[${PROJECT_NAME}]: ${CMAKE_CURRENT_SOURCE_DIR}")

add_executable(thread_affinity thread_affinity.cpp)
set_property(TARGET thread_affinity PROPERTY FOLDER "system/linux")
target_link_libraries(thread_affinity pthread)
