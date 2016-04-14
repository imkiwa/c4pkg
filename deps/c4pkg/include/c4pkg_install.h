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
