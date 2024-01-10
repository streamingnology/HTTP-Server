# get dep name from *.cmake file, for example. spdlog.cmake -> spdlog
# string(REGEX REPLACE ".*/(.*).cmake" "\\1" DEP_NAME ${CMAKE_PARENT_LIST_FILE})

function(get_dep_name_and_source_path DEP_NAME DEP_SOURCE_PATH)
    # get dep name from *.cmake file, for example. spdlog.cmake -> spdlog
    string(REGEX REPLACE ".*/(.*).cmake" "\\1" dep_name ${CMAKE_PARENT_LIST_FILE})

    set(${DEP_NAME} ${dep_name} PARENT_SCOPE)
    
    set(${DEP_SOURCE_PATH} "${CMAKE_BINARY_DIR}/dep-src/${dep_name}" PARENT_SCOPE)
endfunction()

function(get_current_dir_name current_dir_name)
    # remove last end of "/"
    string(REGEX REPLACE "/$" "" CURRENT_DIR_ABSOLUTE ${CMAKE_CURRENT_SOURCE_DIR})

    # get current relative dir name and set target name
    string(REGEX REPLACE ".*/(.*)" "\\1" CURRENT_DIR_NAME ${CURRENT_DIR_ABSOLUTE})

    set(${current_dir_name} ${CURRENT_DIR_NAME} PARENT_SCOPE)
endfunction()
