cmake_minimum_required(VERSION 3.9)

set(PROJECT_NAME cpp)
project(${PROJECT_NAME})

set(CMAKE_CXX_STANDARD 17) #-stdc++17
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

message(STATUS "Configure project[${PROJECT_NAME}]: ${CMAKE_CURRENT_SOURCE_DIR}")

add_executable(dynamic_cast dynamic_cast.cpp)
set_property(TARGET dynamic_cast PROPERTY FOLDER "languages/cpp")

add_executable(function_hiding function_hiding.cpp)
set_property(TARGET function_hiding PROPERTY FOLDER "languages/cpp")

add_executable(function_overloading function_overloading.cpp)
set_property(TARGET function_overloading PROPERTY FOLDER "languages/cpp")

add_executable(function_overriding function_overriding.cpp)
set_property(TARGET function_overriding PROPERTY FOLDER "languages/cpp")

add_executable(friendly friendly.cpp)
set_property(TARGET friendly PROPERTY FOLDER "languages/cpp")