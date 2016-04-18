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


#include "c4pkg.h"
#include "buffer_utils.h"

#include "private/package.h"

ERROR_BUFFER(package);

package_t package_new()
{
  package_t p = (package_t) malloc(sizeof(struct c4pkg_package_s));
  if (!p) {
    return NULL;
  }
  
  memset(p, '\0', sizeof(struct c4pkg_package_s));
  return p;
}

package_t package_open_buffer(const char *buffer, size_t bufsz)
{
  package_t pkg = package_new();
  if (!pkg) {
    package_set_error("Internal Error: Failed to allocate memory for package.");
    goto fail;
  }
  
  pkg->zip = zip_open_buffer(buffer, bufsz);
  if (!pkg->zip) {
    package_set_error("Internal Error: Failed to open zip stream.");
    goto fail;
  }
  
  zipentry_t m = zip_lookup(pkg->zip, C4PKG_MANIFEST);
  if (!m) {
    package_set_error("No '" C4PKG_MANIFEST "' was found in zip stream.");
    goto fail;
  }
  
  size_t sz = zipentry_get_size(m);
  if (sz == 0) {
    package_set_error("Invalid length of manifest.");
    goto fail;
  }
  
  char *mbuf = (char*) malloc(sizeof(char) * (sz + 1));
  if (!mbuf) {
    package_set_error("Internal Error: Failed to allocate memory for manifest.");
    goto fail;
  }
  
  zipentry_decompress(m, mbuf, sz);
  mbuf[sz] = '\0';
  
  pkg->p_info = pkginfo_parse_buffer(mbuf);
  free(mbuf);
  
  if (!pkg->p_info) {
    package_set_error("Failed to parse manifest: %s", pkginfo_get_error());
    goto fail;
  }
  
  /////
  return pkg;

fail:
  if (pkg) {
    package_close(pkg);
  }
  return NULL;
}

package_t package_open_file(const char *path)
{
  if (!path) {
    return false;
  }
  
  int fd = open(path, O_RDONLY);
  if (fd < 0) {
    return false;
  }
  
  package_t ret = package_open_fd(fd);
  close(fd);
  return ret;
}

package_t package_open_fp(FILE *fp)
{
  if (!fp) {
    return NULL;
  }
  
  return package_open_fd(fileno(fp));
}

package_t package_open_fd(int fd)
{
  ssize_t sz;
  char *buffer = buffer_readall_fd(fd, &sz);
  if (!buffer) {
    return NULL;
  }
  
  package_t info = package_open_buffer(buffer, (size_t) sz);
  if (!info) {
    return NULL;
  }
  
  free(buffer);
  return info;
}

void package_close(package_t pkg)
{
  if (!pkg) {
    return;
  }
  
  if (pkg->zip) {
    zip_close(pkg->zip);
  }
  
  if (pkg->p_info) {
    pkginfo_delete(pkg->p_info);
  }
  
  free(pkg);
}
