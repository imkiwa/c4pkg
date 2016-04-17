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


#include "buffer_utils.h"

#define TYPE_SIZE sizeof(char)

char* buffer_readall_fd(int fd, ssize_t *psz)
{
  ssize_t sz = 2; // '\0'
  char buffer[1];
  char *ret = (char*) malloc(TYPE_SIZE * sz);
  
  if (!ret) {
    return NULL;  
  }
  
  while (read(fd, buffer, 1) == 1) {
    ret[sz-2] = buffer[0];
    ret[sz-1] = '\0';
    
    sz++;
    ret = (char*) realloc(ret, TYPE_SIZE * sz);
    if (!ret) {
      return NULL;
    }
  }
  
  if (psz) {
    *psz = sz;
  }
  
  return ret;
}
