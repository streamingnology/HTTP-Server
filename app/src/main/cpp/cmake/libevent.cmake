include(util)

get_dep_name_and_source_path(DEP_NAME DEP_SOURCE_PATH)

set(DEP_GIT_URL "https://github.com/libevent/libevent.git")
set(DEP_GIT_TAG "release-2.1.12-stable")
set(DEP_SRC_DIR ${DEP_SOURCE_PATH})

include(FetchContent)
FetchContent_Declare(${DEP_NAME}
    GIT_REPOSITORY ${DEP_GIT_URL}
    GIT_TAG ${DEP_GIT_TAG}
    SOURCE_DIR ${DEP_SRC_DIR}
)

set(EVENT__DISABLE_OPENSSL ON CACHE INTERNAL "")
set(EVENT__DISABLE_DEBUG_MODE ON CACHE INTERNAL "")
set(EVENT__DISABLE_BENCHMARK ON CACHE INTERNAL "")
set(EVENT__DISABLE_TESTS ON CACHE INTERNAL "")
set(EVENT__DISABLE_REGRESS ON CACHE INTERNAL "")
set(EVENT__DISABLE_SAMPLES ON CACHE INTERNAL "")

fetchcontent_makeavailable(${DEP_NAME})