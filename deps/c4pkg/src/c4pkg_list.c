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


#include <unistd.h>
#include <limits.h>

#include "c4pkg.h"
#include "string_utils.h"

char* c4pkg_get_list_dir(const char *name)
{
  if (!name) {
    return NULL;
  }
  
  return string_concat(C4PKG_LIST_PATH, "/", name, NULL);
}

char* c4pkg_get_list_file(const char *name)
{
  if (!name) {
    return NULL;
  }
  
  return string_concat(C4PKG_LIST_PATH, "/", name, "/", C4PKG_LIST_FILE, NULL);
}

char* c4pkg_get_install_dir(const char *name)
{
  if (!name) {
    return NULL;
  }
  
  return string_concat(C4PKG_PKG_PATH, "/", name, NULL);
}

char* c4pkg_get_manifest_file(const char *name)
{
  if (!name) {
    return NULL;
  }
  
  return string_concat(C4PKG_LIST_PATH, "/", name, "/", C4PKG_MANIFEST, NULL);
}

bool c4pkg_list_dump_file(FILE *to, package_t pkg)
{
  if (!to || !pkg) {
    return false;
  }
  
  pkginfo_t i = package_get_info(pkg);
  
  fprintf(to, "count: %d\n", i->p_file_count);
  for (int n=0; n<i->p_file_count; ++n) {
    if (i->p_files[n]) {
      fprintf(to, "%s\n", i->p_files[n]);
    }
  }
  
  return true;
}

bool c4pkg_list_read_file(FILE *from, package_t pkg)
{
  if (!from || !pkg) {
    return false;
  }
  
  static char fpath[PATH_MAX] = {0};
  static char buf[16] = {0};
  static int count = 0;
  
  pkginfo_t info = package_get_info(pkg);
  
  fgets(buf, 16, from);
  sscanf(buf, "count: %d", &count);
  if (count < 0) {
    goto fail;
  }
  
  info->p_file_count = count;
  info->p_files = (char**) malloc(sizeof(char*) * count);
  if (!info->p_files) {
    goto fail;
  }
  memset(info->p_files, '\0', sizeof(char*) * count);
  
  for (int i=0; i<count; ++i) {
    if (!fgets(fpath, PATH_MAX, from)) {
      goto fail;
    }
    
    size_t sz = strlen(fpath);
    if (fpath[sz - 1] == '\n') {
      fpath[sz - 1] = '\0';
    }
    
    info->p_files[i] = strdup(fpath);
    if (!info->p_files[i]) {
      goto fail;
    }
  }
  
  return true;

fail:
  if (info->p_files) {
    for (int i=0; i<info->p_file_count; ++i) {
      if (info->p_files[i]) {
        free(info->p_files[i]);
      }
    }
  }
  
  info->p_file_count = 0;
  info->p_files = NULL;
  
  return false;
}
