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
