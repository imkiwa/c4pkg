#pragma once

#include "c4pkg_package.h"
#include "c4pkg_list.h"
#include "error_utils.h"

#define QUERY_ALL      0xffffffff
#define QUERY_MANIFEST 0x00000001
#define QUERY_FILES    0x00000002

ERROR_BUFFER_DEF(query);

package_t c4pkg_query(const char *name, int flags);
