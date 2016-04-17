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

#include "c4pkg_package.h"
#include "c4pkg_list.h"
#include "error_utils.h"

#define QUERY_ALL      0xffffffff
#define QUERY_MANIFEST 0x00000001
#define QUERY_FILES    0x00000002

ERROR_BUFFER_DEF(query);

package_t c4pkg_query(const char *name, int flags);
