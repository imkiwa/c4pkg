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

#include <stdbool.h>
#include <unistd.h>

bool mkdir_recursive(const char *path, mode_t mode);

bool chmod_recursive(const char *path, mode_t mode, bool include_self);

bool chown_recursive(const char *path, uid_t owner, uid_t group, bool include_self);

bool unlink_recursive(const char *path, bool include_self);

bool mkdir_parent(const char *path, mode_t mode);
