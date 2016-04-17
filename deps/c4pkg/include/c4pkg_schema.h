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

#define SCHEMA_LOCAL_STR "local://"
#define SCHEMA_LOCAL_LEN 8

#define SCHEMA_FILE_STR  "file://"
#define SCHEMA_FILE_LEN  7

#define SCHEMA_GIT_STR   "git://"
#define SCHEMA_GIT_LEN   6

typedef struct c4pkg_schema_s schema_t;
typedef enum c4pkg_schema_type_s schtype_t;

enum c4pkg_schema_type_s
{
  SCHEMA_LOCAL = SCHEMA_LOCAL_LEN,
  SCHEMA_FILE  = SCHEMA_FILE_LEN,
  SCHEMA_GIT   = SCHEMA_GIT_LEN
};

struct c4pkg_schema_s
{
  schtype_t s_type;
  char *s_url;
};


bool c4pkg_schema_parse(const char *url, schema_t *schema);
