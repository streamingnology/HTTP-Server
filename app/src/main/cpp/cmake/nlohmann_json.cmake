include(util)

get_dep_name_and_source_path(DEP_NAME DEP_SOURCE_PATH)

set(DEP_GIT_URL "https://github.com/nlohmann/json.git")
set(DEP_GIT_TAG "v3.11.3")
set(DEP_SRC_DIR ${DEP_SOURCE_PATH})

include(FetchContent)
FetchContent_Declare(${DEP_NAME}
    GIT_REPOSITORY ${DEP_GIT_URL}
    GIT_TAG ${DEP_GIT_TAG}
    SOURCE_DIR ${DEP_SRC_DIR}
)

set(JSON_Install ON CACHE INTERNAL "")
set(JSON_BuildTests OFF CACHE INTERNAL "")

fetchcontent_makeavailable(${DEP_NAME})