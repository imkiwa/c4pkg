add_library  (c4pkg_utils
    src/buffer_utils.c
    src/fs_utils.c
    src/string_utils.c
  )

target_link_libraries (c4pkg_utils
    
  )

install (
  TARGETS c4pkg_utils
  
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

