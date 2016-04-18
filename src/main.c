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


#include <stdio.h>
#include <string.h>

#include "c4pkg.h"

int do_query(const char *name, bool all)
{
  int flags = QUERY_MANIFEST;
  if (all) {
    flags = QUERY_ALL;
  }
  
  package_t pkg = c4pkg_query(name, flags);
  if (!pkg) {
    printf("%s\n", query_get_error());
    return 1;
  }
    
  c4pkg_print_package_info(pkg);
  package_close(pkg);
  return 0;
}

int main(int argc, char **argv)
{
  if (argc == 1) {
    return 0;
  }
  
  if (strcmp("-Q", argv[1]) == 0) {
    return do_query(argv[2], false);
  
  } else if (strcmp("-Qa", argv[1]) == 0) {
    return do_query(argv[2], true);
  
  } else if (strcmp("-R", argv[1]) == 0) {
    return c4pkg_remove(argv[2]) ? 0 : 1;
    
  } else if (strcmp("-S", argv[1]) == 0) {
    if (!c4pkg_install_file(argv[2])) {
      printf("%s\n", install_get_error());
    }
  
  } else if (strcmp("-Sg", argv[1]) == 0) {
    if (!c4pkg_install_git(argv[2])) {
      printf("%s\n", install_get_error());
    }
  }
  
  return 0;
}
