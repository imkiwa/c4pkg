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


#pragma once

#include <stdio.h>
#include <stdbool.h>

#include "zipfile/zipfile.h"
#include "error_utils.h"

ERROR_BUFFER_DEF(zip);

zipfile_t zip_open_file(const char *path);

zipfile_t zip_open_fp(FILE *fp);

zipfile_t zip_open_fd(int fd);

int zip_get_entry_count(zipfile_t zip);

static inline zipfile_t zip_open_buffer(const char *buffer, size_t sz)
{
  return init_zipfile((void*) buffer, sz);
}

static inline void zip_close(zipfile_t zip)
{
  release_zipfile(zip);
}

static inline zipentry_t zip_foreach(zipfile_t file, void** cookie)
{
  return iterate_zipfile(file, cookie);
}

static inline zipentry_t zip_lookup(zipfile_t zip, const char *name)
{
  return lookup_zipentry(zip, name);
}

bool zipentry_extract_to(zipentry_t entry, const char *dir);

static inline size_t zipentry_get_size(zipentry_t e)
{
  return get_zipentry_size(e);
}

static inline char* zipentry_get_name(zipentry_t e)
{
  return get_zipentry_name(e);
}

static inline int zipentry_decompress(zipentry_t entry, void* buf, int bufsize)
{
  return decompress_zipentry(entry, buf, bufsize);
}
