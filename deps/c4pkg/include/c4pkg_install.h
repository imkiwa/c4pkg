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
#include <stdbool.h>

#include "c4pkg_zip.h"
#include "c4pkg_schema.h"
#include "c4pkg_config.h"
#include "error_utils.h"

ERROR_BUFFER_DEF(install);

typedef struct c4pkg_install_opt_s inst_opt_t;

struct c4pkg_install_opt_s
{
  /**
   * install location
   */
  char *o_inst_dir;
  
  /**
   * package source
   *
   * source url
   *  file:///<path>/<to>/<package>
   *  git://<username>/<repository>
   */
  const char *o_src;
  size_t o_src_length;
  
  /**
   * package source type
   */
  schema_t o_schema;
  
  bool o_update_when_exists;
  bool o_ignore_dependencies;
  
  /**
   * if print_fn == NULL,
   * nothing will be printed during the installation
   */
  int (*print_fn)(const char *fmt, ...);
};


bool c4pkg_install_with_opt(inst_opt_t *opt);

bool c4pkg_install(const char *url);

bool c4pkg_install_file(const char *file);

bool c4pkg_install_git(const char *git);

bool c4pkg_install_fp(FILE *fp);

bool c4pkg_install_fd(int fd);

bool c4pkg_install_buffer(const char *buffer, size_t bufsz);

