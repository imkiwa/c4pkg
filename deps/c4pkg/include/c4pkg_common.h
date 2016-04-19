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
#include <unistd.h>
#include "c4pkg_package.h"

static inline bool c4pkg_check_root()
{
  return geteuid() == 0 || getuid() == 0;
}


void c4pkg_print_package_info(package_t pkg);

bool c4pkg_set_owner_c4droid();


#define c4pkg_printf(fmt, ...) c4pkg_fprintf(stdout, fmt, ##__VA_ARGS__)

int c4pkg_fprintf(FILE *fp, const char *fmt, ...);
