add_library  (c4pkg_zip
    src/zipfile.c
    src/centraldir.c
    src/c4pkg_zip.c
  )

target_link_libraries (c4pkg_zip
    z c4pkg_utils
  )

install (
  TARGETS c4pkg_zip
  
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
