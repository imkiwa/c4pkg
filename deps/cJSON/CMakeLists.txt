add_library  (cJSON 
  src/cJSON.c
  src/cJSON_Utils.c)

target_link_libraries (cJSON
    m
  )

install (
  TARGETS cJSON
  
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

