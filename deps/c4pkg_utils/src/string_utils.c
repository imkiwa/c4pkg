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


#include "string_utils.h"

#include <malloc.h>
#include <string.h>

char* string_concat(const char *l, ...)
{
  if (!l) {
    return NULL;
  }
  
  size_t sz = strlen(l) + 1; // '\0'
  char *str = (char*) malloc(sizeof(char) * sz);
  if (!str) {
    return NULL;
  }
  
  memset(str, '\0', sz);
  strcpy(str, l);
  
  va_list arg;
  va_start(arg, l);
  
  size_t psz = 0;
  const char *p = NULL;
  while ((p = va_arg(arg, const char*))) {
    psz = strlen(p);
    if (psz == 0) {
      continue;
    }
    
    sz += psz;
    str = (char*) realloc(str, sizeof(char) * sz);
    if (!str) {
      goto fail;
    }
    
    strcat(str, p);
    str[sz - 1] = '\0';
  }
  
  va_end(arg);
  return str;
  
fail:
  if (str) {
    free(str);
  }
  va_end(arg);
  return NULL;
}
