add_library  (cJSON 
  src/cJSON.c
  src/cJSON_Utils.c)

target_link_libraries (cJSON
    m
  )
