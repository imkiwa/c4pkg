#pragma once

#include <stdbool.h>
#include "error_utils.h"

ERROR_BUFFER_DEF(remove);

bool c4pkg_remove(const char *name);
