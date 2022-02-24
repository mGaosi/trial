cmake_minimum_required(VERSION 3.9)

set(PROJECT_NAME cpp)
project(${PROJECT_NAME})

set(CMAKE_CXX_STANDARD 17) #-stdc++17
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

message(STATUS "Configure project[${PROJECT_NAME}]: ${CMAKE_CURRENT_SOURCE_DIR}")

add_executable(dynamic_cast dynamic_cast.cpp)
set_property(TARGET dynamic_cast PROPERTY FOLDER "languages/cpp")
