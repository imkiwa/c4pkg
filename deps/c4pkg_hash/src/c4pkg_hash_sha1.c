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


#include <stdlib.h>
#include <stdio.h>

#include "c4pkg_hash.h"
#include "private/sha.h"

uint8_t* c4pkg_hash_sha1(char *data, int len, int *retsz)
{
  if (!data || len < 0) {
    return NULL;
  }
  
  uint8_t *digest = (uint8_t*) malloc(sizeof(uint8_t) * SHA_DIGEST_SIZE);
  if (!digest) {
    return NULL;
  }
  
  if (retsz) {
    *retsz = SHA_DIGEST_SIZE;
  }
  
  SHA_hash(data, len, digest);
  return digest;
}

char* c4pkg_hash_sha1_string(char *data, int len)
{
  if (!data || len < 0) {
    return NULL;
  }
  
  int sz;
  uint8_t *digest = c4pkg_hash_sha1(data, len, &sz);
  if (!digest) {
    return NULL;
  }
  
  char *str = c4pkg_hash_to_string(digest, sz);
  free(digest);
  
  if (!str) {
    return NULL;
  }
  
  return str;
}

char* c4pkg_hash_to_string(uint8_t *digest, int len)
{
  if (!digest) {
    return NULL;
  }
  
  int need = len * 2 + 1; // '\0';
  char *str = (char*) malloc(sizeof(char) * need);
  if (!str) {
    return NULL;
  }
  
  for (int i=0; i<len; ++i) {
    snprintf(str+i, 3, "%02x", digest[i]);
  }
  
  return str;
}
