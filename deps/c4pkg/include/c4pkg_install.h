#include <stdio.h>
#include <stdbool.h>

#include "c4pkg_zip.h"
#include "error_utils.h"

#define C4PKG_DATA_ZIP "data.zip"

ERROR_BUFFER_DEF(install);

typedef struct c4pkg_install_opt_s inst_opt_t;
typedef enum c4pkg_install_source_e inst_src_t;

enum c4pkg_install_source_e
{
  SRC_GIT, SRC_FILE, SRC_STREAM
};

struct c4pkg_install_opt_s
{
  /**
   * install location
   */
  char *o_inst_dir;
  
  /**
   * package source
   *
   * if o_src == SRC_GIT:
   *   username/repository
   *
   * if o_src == SRC_FILE:
   *   /path/to/package.zip
   *
   * if o_src == SRC_STREAM:
   *   <buffer>
   */
  const char *o_src;
  size_t o_src_length;
  
  /**
   * package source type
   */
  inst_src_t o_src_type;
  
  bool o_update_when_exists;
  bool o_ignore_dependencies;
  
  /**
   * if print_fn == NULL,
   * nothing will be printed during the installation
   */
  int (*print_fn)(const char *fmt, ...);
};


bool c4pkg_install_with_opt(inst_opt_t *opt);

bool c4pkg_install_git(const char *repo);

bool c4pkg_install_file(const char *file);

bool c4pkg_install_fp(FILE *fp);

bool c4pkg_install_fd(int fd);

bool c4pkg_install_buffer(const char *buffer, size_t bufsz);
