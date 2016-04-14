add_library  (c4pkg
    src/c4pkg_install.c
    src/c4pkg_package.c
    src/c4pkg_parser.c
    src/c4pkg_list.c
    src/c4pkg_query.c
    src/c4pkg_schema.c
  )

target_link_libraries (c4pkg
    cJSON c4pkg_zip c4pkg_utils
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
