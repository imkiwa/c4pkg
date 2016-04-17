#pragma once

#include "error_utils.h"

#include "c4pkg_config.h"

ERROR_BUFFER_DEF(pkginfo);

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
  
  char *p_checksum;
  
  /**
   * content of manifest.json
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

pkginfo_t pkginfo_parse_buffer(const char *buffer);

pkginfo_t pkginfo_parse_file(const char *path);

pkginfo_t pkginfo_parse_fp(FILE *fp);

pkginfo_t pkginfo_parse_fd(int fd);

void pkginfo_delete(pkginfo_t info);

const char* pkginfo_get_error();
