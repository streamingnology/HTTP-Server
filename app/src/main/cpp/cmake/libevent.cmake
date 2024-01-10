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

option(EVENT__DISABLE_OPENSSL
        "Define if libevent should build without support for OpenSSL encryption" ON)

fetchcontent_makeavailable(${DEP_NAME})