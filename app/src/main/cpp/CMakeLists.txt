cmake_minimum_required(VERSION 3.22.1)

project("httpserver")

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake;${CMAKE_MODULE_PATH}")

include(nlohmann_json)
add_subdirectory(asio2-2.8)

file(GLOB_RECURSE source_files src/*.cpp)
file(GLOB_RECURSE header_files src/*.h)

add_library(${CMAKE_PROJECT_NAME} SHARED
        src/log.h
        src/base64.cpp
        src/base64.h
        src/resources/res.h
        src/HttpServerJNI.cpp
        src/HttpServer.cpp
        src/actions/directory.cpp)

target_link_libraries(${CMAKE_PROJECT_NAME} android log asio2 nlohmann_json)
target_compile_features(${CMAKE_PROJECT_NAME} PUBLIC cxx_std_17)
