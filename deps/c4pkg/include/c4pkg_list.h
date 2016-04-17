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

#include "c4pkg_config.h"
#include "c4pkg_install.h"
#include "c4pkg_package.h"

char* c4pkg_get_list_dir(const char *name);

char* c4pkg_get_list_file(const char *name);

char* c4pkg_get_manifest_file(const char *name);

bool c4pkg_list_dump_file(FILE *to, package_t pkg);

bool c4pkg_list_read_file(FILE *from, package_t pkg);
