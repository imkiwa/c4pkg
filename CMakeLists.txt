cmake_minimum_required (VERSION 2.6)

PROJECT (c4pkg)

set (CMAKE_C_FLAGS "-fPIC --pie -std=c99 -g")
set (CMAKE_EXE_LINKER_FLAGS "-fPIC --pie")

set (DEP_DIR "${PROJECT_SOURCE_DIR}/deps")

set (SRC_cJSON "${DEP_DIR}/cJSON")
set (SRC_c4pkg "${DEP_DIR}/c4pkg")
set (SRC_c4pkg_utils "${DEP_DIR}/c4pkg_utils")
set (SRC_c4pkg_zip "${DEP_DIR}/c4pkg_zip")

include_directories ("${PROJECT_SOURCE_DIR}/include")
include_directories ("${SRC_c4pkg}/include")
include_directories ("${SRC_c4pkg_utils}/include")
include_directories ("${SRC_c4pkg_zip}/include")
include_directories ("${SRC_cJSON}/include")

add_subdirectory ("${SRC_cJSON}")
add_subdirectory ("${SRC_c4pkg}")
add_subdirectory ("${SRC_c4pkg_utils}")
add_subdirectory ("${SRC_c4pkg_zip}")

add_executable (c4pkg-cli
    src/main.c
  )
target_link_libraries (c4pkg-cli
    c4pkg
  )


install (
  TARGETS c4pkg-cli
  
  RUNTIME DESTINATION bin
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib
)

install (
  DIRECTORY include docs
  
  DESTINATION .
  
  PATTERN "*.h"
  PERMISSIONS OWNER_WRITE OWNER_READ GROUP_READ
)

install (
  FILES flags.txt
  
  DESTINATION .
)
