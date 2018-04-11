# For more information about using CMake with Android Studio, read the
# documentation: https://d.android.com/studio/projects/add-native-code.html

# Sets the minimum version of CMake required to build the native library.

cmake_minimum_required(VERSION 3.4.1)

set(NOCOMPANY_SOURCE_DIR ${CMAKE_SOURCE_DIR}/../)
set(STATIC_LIBS_DIR ${NOCOMPANY_SOURCE_DIR}/app/libs)

# Creates and names a library, sets it as either STATIC
# or SHARED, and provides the relative paths to its source code.
# You can define multiple libraries, and CMake builds them for you.
# Gradle automatically packages shared libraries with your APK.

add_library( # Sets the name of the library.
             httpserver-jni

             # Sets the library as a shared library.
             SHARED

             # Provides a relative path to your source file(s).
             src/main/cpp/HttpServer.cpp
             src/main/cpp/Log.cpp
             src/main/cpp/MageResults.cpp
             src/main/cpp/IHttpServer.cpp
             src/main/cpp/HttpServerJNI.cpp
             )

include_directories(
                    include/${ANDROID_ABI}
                    ../third-party/rapidjson/include
                   )

# Searches for a specified prebuilt library and stores the path as a
# variable. Because CMake includes system libraries in the search path by
# default, you only need to specify the name of the public NDK library
# you want to add. CMake verifies that the library exists before
# completing its build.

find_library( # Sets the name of the path variable.
              log-lib

              # Specifies the name of the NDK library that
              # you want CMake to locate.
              log )

add_library(event SHARED IMPORTED GLOBAL)
set_property(TARGET event PROPERTY IMPORTED_LOCATION ${STATIC_LIBS_DIR}/${ANDROID_ABI}/libevent.so)

# Specifies libraries CMake should link to your target library. You
# can link multiple libraries, such as libraries you define in this
# build script, prebuilt third-party libraries, or system libraries.

target_link_libraries( # Specifies the target library.
                       httpserver-jni
                       event
                       ${log-lib} )