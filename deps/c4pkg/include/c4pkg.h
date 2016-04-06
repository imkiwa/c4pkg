#pragma once

#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>

#include "c4pkg_config.h"
#include "c4pkg_package.h"
#include "c4pkg_install.h"
#include "c4pkg_list.h"

static inline bool c4pkg_check_root()
{
  return geteuid() == 0 || getuid() == 0;
}

static inline int c4pkg_build_flags()
{
  return printf(" -fPIC --pie -I '%s' -L '%s' -lz -lm -lcJSON -lc4pkg -lc4pkg_zip -lc4pkg_utils ", C4PKG_PKG_INCLUDE_PATH, C4PKG_PKG_LIB_PATH);
}
