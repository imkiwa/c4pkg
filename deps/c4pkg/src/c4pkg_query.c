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


#include "c4pkg_query.h"
#include "c4pkg_list.h"

#include "private/package.h"

ERROR_BUFFER(query);

package_t c4pkg_query(const char *name, int flags)
{
  if (!name) {
    return NULL;
  }
  
  char *mani_path = c4pkg_get_manifest_file(name);
  char *list_path = c4pkg_get_list_file(name);
  
  if (!list_path || !mani_path) {
    query_set_error("Internal Error: Failed to get package info file");
    return NULL;
  }
  
  package_t pkg = package_new();
  if (!pkg) {
    query_set_error("Internal Error: Failed to allocated memory");
    return NULL;
  }
  
  if (flags & QUERY_MANIFEST) {
    pkg->p_info = pkginfo_parse_file(mani_path);
    if (!pkg->p_info) {
      query_set_error("%s", pkginfo_get_error());
      goto fail;
    }
  }
  
  if (flags & QUERY_FILES) {
    FILE *fp = fopen(list_path, "r");
    if (!fp) {
      query_set_error("Failed to open list file '%s'", list_path);
      goto fail;
    }
    
    if (!c4pkg_list_read_file(fp, pkg)) {
      query_set_error("Failed to read List file");
      fclose(fp);
      goto fail;
    }
    
    fclose(fp);
  }
  
  return pkg;
  
fail:
  package_close(pkg);
  return NULL;
}
