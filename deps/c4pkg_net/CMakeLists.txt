add_library  (c4pkg_net
    src/c4pkg_download.c
  )

target_link_libraries (c4pkg_net
    c4pkg_curl c4pkg_ssl c4pkg_crypto
  )

install (
  TARGETS c4pkg_net
  
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
