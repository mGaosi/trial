cmake_minimum_required(VERSION 3.9)

set_property(GLOBAL PROPERTY USE_FOLDERS On)

include("cmake/project.cmake")

project(trial)
add_subdirectory("languages/c")
add_subdirectory("languages/cpp")
add_subdirectory("system/")
