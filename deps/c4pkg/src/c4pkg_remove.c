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
#include <unistd.h>
#include <sys/types.h>

#include "c4pkg_remove.h"
#include "c4pkg_query.h"
#include "c4pkg_list.h"
#include "fs_utils.h"
#include "string_utils.h"

#include "private/remove.h"

ERROR_BUFFER(remove);

bool c4pkg_remove_package_files(package_t pkg)
{
  const char *name = package_get_name(pkg);
  
  char *list_dir = c4pkg_get_list_dir(name);
  char *inst_dir = c4pkg_get_install_dir(name);
  if (!list_dir || !inst_dir) {
    remove_set_error("Failed to get package dir");
    printf("%s\n", remove_get_error());
    return false;
  }
  
  if (!unlink_recursive(inst_dir, true)) {
    remove_set_error("Failed to remove package files dir");
    goto fail;
  }
  
  if (!unlink_recursive(list_dir, true)) {
    remove_set_error("Failed to remove list dir");
    goto fail;
  }
  
  free(list_dir);
  free(inst_dir);
  return true;

fail:
  free(list_dir);
  free(inst_dir);
  return false;
}

bool c4pkg_remove(const char *name)
{
  if (!name) {
    return false;
  }
  
  package_t pkg = c4pkg_query(name, QUERY_ALL);
  if (!pkg) {
    remove_set_error("Package '%s' is not installed", name);
    printf("%s\n", remove_get_error());
    goto fail;
  }
  
  if (!c4pkg_remove_package_files(pkg)) {
    printf("%s\n", remove_get_error());
    goto fail;
  }
  
  printf("=> Package '%s' was successfully removed\n", name);
  
  package_close(pkg);
  return true;

fail:
  package_close(pkg);
  return false;
}
