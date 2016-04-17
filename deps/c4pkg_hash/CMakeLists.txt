add_library  (c4pkg_hash
    src/sha.c
    src/c4pkg_hash_sha1.c
  )

target_link_libraries (c4pkg_hash
  )

install (
  TARGETS c4pkg_hash
  
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
