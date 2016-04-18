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


#include "c4pkg_zip.h"
#include "buffer_utils.h"
#include "fs_utils.h"
#include "private/zip.h"

ERROR_BUFFER(zip);

zipfile_t zip_open_file(const char *path)
{
  if (!path) {
    return false;
  }
  
  int fd = open(path, O_RDONLY);
  if (fd < 0) {
    return false;
  }
  
  zipfile_t ret = zip_open_fd(fd);
  close(fd);
  return ret;
}

zipfile_t zip_open_fp(FILE *fp)
{
  if (!fp) {
    return NULL;
  }
  
  return zip_open_fd(fileno(fp));
}

zipfile_t zip_open_fd(int fd)
{
  ssize_t sz;
  char *buffer = buffer_readall_fd(fd, &sz);
  if (!buffer) {
    return NULL;
  }
  
  zipfile_t info = zip_open_buffer(buffer, (size_t) sz);
  if (!info) {
    return NULL;
  }
  
  free(buffer);
  return info;
}

int zip_get_entry_count(zipfile_t zip)
{
  Zipfile *z = (Zipfile*) zip;
  return z ? z->entryCount : 0;
}

bool zipentry_extract_to(zipentry_t entry, const char *dir)
{
  if (!entry || !dir) {
    return false;
  }
  
  const char *name = zipentry_get_name(entry);
  size_t esz = zipentry_get_size(entry);
  
  size_t name_len = strlen(name);
  size_t dir_len = strlen(dir);
  if (name_len == 0 || dir_len == 0) {
    return false;
  }
  
  size_t total = name_len + dir_len + 1;
  bool increased = false;
  
  if (dir[dir_len - 1] != '/') {
    total++;
    increased = true;
  }
  
  char *dest_path = (char*) malloc(sizeof(char) * total);
  if (!dest_path) {
    return false;
  }
  
  memset(dest_path, '\0', total);
  strcat(dest_path, dir);
  if (increased) {
    // make sure that at least one slash in path string
    strcat(dest_path, "/");
  }
  strcat(dest_path, name);
  
  if (name[name_len - 1] == '/' && esz == 0) {
    // Is a directory, just create it.
    bool r = mkdir_recursive(dest_path, 0755);
    free(dest_path);
    return r;
  }
  
  if (!mkdir_parent(dest_path, 0755)) {
    goto fail;
  }
  
  FILE *dest = fopen(dest_path, "wb");
  if (!dest) {
    goto fail;
  }
  
  char *ebuf = (char*) malloc(sizeof(char) * (esz + 1));
  if (!ebuf) {
    goto fail_file;
  }
  
  zipentry_decompress(entry, ebuf, esz);
  ebuf[esz] = '\0';
  
  fwrite(ebuf, esz, 1, dest);
  
  fclose(dest);
  free(dest_path);
  return true;

fail_file:
  fclose(dest);
fail:
  free(dest_path);
  return false;
}
