add_library  (apollo_getopt
    src/getopt.c
  )

target_link_libraries (apollo_getopt
    
  )

install (
  TARGETS apollo_getopt
  
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
