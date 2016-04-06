#pragma once

#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include "c4pkg_zip.h"
#include "error_utils.h"

typedef struct c4pkg_package_s* package_t;
typedef struct c4pkg_package_info_s* pkginfo_t;

struct c4pkg_package_info_s
{
  /**
   * primary info.
   */
  char *p_name;
  size_t p_name_length;
  
  char *p_desc;
  size_t p_desc_length;
  
  /**
   * the content of manifest.json
   */
  char *p_mnfs;
  size_t p_mnfs_length;
  
  /**
   * version.
   */
  int p_major;
  int p_minor;
  int p_patch;
  
  /**
   * flag
   */
  bool p_inst;
  
  /**
   * dependencies
   */
  int p_dep_count;
  pkginfo_t *p_deps;
  
  /**
   * contents
   */
  int p_file_count;
  char **p_files;
};

struct c4pkg_package_s
{
  zipfile_t zip;
  
  /**
   * User cookie.
   */
  void *cookie;
  
  pkginfo_t p_info;
};

#include "c4pkg_parser.h"


ERROR_BUFFER_DEF(package);

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

