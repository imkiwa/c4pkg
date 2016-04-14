#pragma once

#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>

#include "c4pkg_config.h"
#include "c4pkg_package.h"
#include "c4pkg_install.h"
#include "c4pkg_list.h"
#include "c4pkg_query.h"

static inline bool c4pkg_check_root()
{
  return geteuid() == 0 || getuid() == 0;
}

