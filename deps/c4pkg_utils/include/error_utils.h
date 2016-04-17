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

#include <stdarg.h>

#define ERROR_BUFFER_DEF(prefix) \
  const char* prefix##_get_error()

#define ERROR_BUFFER(prefix) \
  static char prefix##_error_buffer[128]; \
  static void prefix##_set_error(const char *fmt, ...) \
  { \
    va_list arg; \
    va_start(arg, fmt); \
    vsnprintf(prefix##_error_buffer, sizeof(prefix##_error_buffer), fmt, arg); \
    va_end(arg); \
  } \
  \
  ERROR_BUFFER_DEF(prefix) \
  { \
    return prefix##_error_buffer; \
  }
