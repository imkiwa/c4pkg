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
#include <string.h>
#include <stdbool.h>

#include "c4pkg_zip.h"
#include "c4pkg_parser.h"
#include "error_utils.h"

ERROR_BUFFER_DEF(package);

typedef struct c4pkg_package_s* package_t;

struct c4pkg_package_s
{
  zipfile_t zip;
  
  /**
   * User cookie.
   */
  void *cookie;
  
  pkginfo_t p_info;
};


/**
 * Get package info from package_t.
 */
static inline pkginfo_t package_get_info(package_t pkg)
{
  return pkg->p_info;
}

/**
 * Get package's name from package_t.
 */
static inline const char* package_get_name(package_t pkg)
{
  return package_get_info(pkg)->p_name;
}

/**
 * Get package's major version.
 */
static inline int package_get_major_version(package_t pkg)
{
  return package_get_info(pkg)->p_major;
}

/**
 * Get package's major version.
 */
static inline int package_get_minor_version(package_t pkg)
{
  return package_get_info(pkg)->p_minor;
}

/**
 * Get package's major version.
 */
static inline int package_get_patch_version(package_t pkg)
{
  return package_get_info(pkg)->p_patch;
}

/**
 * Check if two packages are the same.
 */
static inline bool package_equals(package_t lhs, package_t rhs)
{
  return strcmp(package_get_name(lhs), package_get_name(rhs)) == 0
      && package_get_patch_version(lhs) == package_get_patch_version(rhs)
      && package_get_minor_version(lhs) == package_get_minor_version(rhs)
      && package_get_major_version(lhs) == package_get_major_version(rhs);
}


/**
 * Open a package from path,
 * return NULL if something	 goes wrong.
 */
package_t package_open_file(const char *path);


/**
 * Open a package from opened FILE,
 * return NULL if something	 goes wrong.
 */
package_t package_open_fp(FILE *fp);


/**
 * Open a package from opened fd,
 * return NULL if something	 goes wrong.
 */
package_t package_open_fd(int fd);


/**
 * Open a package from buffer,
 * return NULL if something goes wrong.
 */
package_t package_open_buffer(const char *buffer, size_t bufsz);


/**
 * Close and release package.
 */
void package_close(package_t pkg);

