cmake_minimum_required (VERSION 2.6)

set (CMAKE_C_FLAGS "-fPIC --pie -std=c99")
set (CMAKE_EXE_LINKER_FLAGS "-fPIC --pie")

set (DEP_DIR "${PROJECT_SOURCE_DIR}/deps")

set (SRC_cJSON "${DEP_DIR}/cJSON")
set (SRC_c4pkg "${DEP_DIR}/c4pkg")

# include_directories ("${PROJECT_SOURCE_DIR}/include")
include_directories ("${SRC_c4pkg}/include")
include_directories ("${SRC_cJSON}/include")

add_subdirectory ("${SRC_cJSON}")
add_subdirectory ("${SRC_c4pkg}")
