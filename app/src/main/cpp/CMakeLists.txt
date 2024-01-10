cmake_minimum_required(VERSION 3.22.1)

project("httpserver")

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake;${CMAKE_MODULE_PATH}")

include(libevent)

add_library(${CMAKE_PROJECT_NAME} SHARED
    # List C/C++ source files with relative paths to this CMakeLists.txt.
    httpserver.cpp)

target_link_libraries(${CMAKE_PROJECT_NAME} android log event)
