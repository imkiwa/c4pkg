/**
 * Copyright (C) 2016  apollo-opensource
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */


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
