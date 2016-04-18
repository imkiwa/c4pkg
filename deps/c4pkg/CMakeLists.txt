add_library  (c4pkg
    src/c4pkg_common.c
    src/c4pkg_install.c
    src/c4pkg_remove.c
    src/c4pkg_package.c
    src/c4pkg_parser.c
    src/c4pkg_list.c
    src/c4pkg_query.c
    src/c4pkg_schema.c
    src/c4pkg_github.c
  )

target_link_libraries (c4pkg
    c4pkg_net cJSON c4pkg_zip c4pkg_utils c4pkg_hash
  )

install (
  TARGETS c4pkg
  
  RUNTIME DESTINATION bin
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib
)

install (
  DIRECTORY include
  
  DESTINATION .
  
  PATTERN "*.h"
  PERMISSIONS OWNER_WRITE OWNER_READ GROUP_READ
)
