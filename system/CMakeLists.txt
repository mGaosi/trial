cmake_minimum_required(VERSION 3.9)

message(STATUS "Configure system projects.")
message(STATUS "CMake is compiling for ${CMAKE_SYSTEM_NAME} ${CMAKE_SYSTEM_VERSION}.")

if(CMAKE_SYSTEM_NAME MATCHES "Windows")
    add_subdirectory(windows)
elseif(CMAKE_SYSTEM_NAME MATCHES "Linux")
    add_subdirectory(linux)
    add_subdirectory(unix)
endif()
