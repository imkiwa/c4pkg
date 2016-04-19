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
#include <stdlib.h>

#include "c4pkg_common.h"
#include "c4pkg_config.h"
#include "buffer_utils.h"
#include "fs_utils.h"

static uid_t get_c4droid_uid_android()
{
  int fd = open("/data/system/packages.list", O_RDONLY);
  if (fd < 0) {
    return 0;
  }
  
  char *buffer = buffer_readall_fd(fd, NULL);
  close(fd);
  
  if (!buffer) {
    return 0;
  }
  
  int c4uid = 0;
  
  // For example, we need 10078
  // com.n0n3m4.droidc 10078 0 /data/data/com.n0n3m4.droidc default none
  if (sscanf(buffer, "com.n0n3m4.droidc %d", &c4uid) == 0) {
    free(buffer);
    return 0;
  }
  
  printf("uid: %d\n", c4uid);
  free(buffer);
  return c4uid;
}

void c4pkg_print_package_info(package_t pkg)
{
  pkginfo_t i = package_get_info(pkg);
  
  c4pkg_printf("Package\n");
  printf(" package: %s\n", i->p_name);
  printf(" description: %s\n", i->p_desc);
  printf(" version: %d.%d.%d\n", i->p_major, i->p_minor, i->p_patch);
  
  printf("\n");
  c4pkg_printf("Package Security\n");
  printf(" checksum: %s\n", i->p_checksum);
  
  if (i->p_deps) {
    printf("\n"); 
    c4pkg_printf("Package Dependencies\n");
    for (int n=0; n<i->p_dep_count; ++n) {
      pkginfo_t d = i->p_deps[n];
      printf(" #%-2d %s(%d.%d.%d)\n", n, d->p_name, d->p_major, d->p_minor, d->p_patch);
    }
  }
  
  if (i->p_files) {
    printf("\n");
    c4pkg_printf("Package Files\n");
    for (int n=0; n<i->p_file_count; ++n) {
      printf(" %s\n", i->p_files[n]);
    }
  }
}

bool c4pkg_set_owner_c4droid()
{
  // current user is not root
  // we have no permission for /data/system/package.list
  if (!c4pkg_check_root()) {
    return true;
  }
  
  uid_t uid = get_c4droid_uid_android();
  if (uid == 0) { // can't be root
    return false;
  }
  
  return chown_recursive(C4PKG_DATA, uid, uid, true);
}

int c4pkg_fprintf(FILE *fp, const char *fmt, ...)
{
  va_list arg;
  va_start(arg, fmt);
  
  int r = fprintf(fp, "\e[1;33m::\e[0m ");
  r += vfprintf(fp, fmt, arg);
  va_end(arg);
  
  return r;
}
