#include "c4pkg_schema.h"

#include <string.h>
#include <malloc.h>


bool c4pkg_schema_parse(const char *url, schema_t *schema)
{
  if (!url || !schema) {
    return false;
  }
  
  if (strncmp(url, SCHEMA_LOCAL_STR, SCHEMA_LOCAL_LEN) == 0) {
    schema->s_type = SCHEMA_LOCAL;
    schema->s_url = strdup(url + SCHEMA_LOCAL_LEN);
  
  } else if (strncmp(url, SCHEMA_FILE_STR, SCHEMA_FILE_LEN) == 0) {
    schema->s_type = SCHEMA_FILE;
    schema->s_url = strdup(url + SCHEMA_FILE_LEN);
  
  } else if (strncmp(url, SCHEMA_GIT_STR, SCHEMA_GIT_LEN) == 0) {
    schema->s_type = SCHEMA_GIT;
    schema->s_url = strdup(url + SCHEMA_GIT_LEN);
  
  } else {
    return false;
  }
  
  return true;
}
