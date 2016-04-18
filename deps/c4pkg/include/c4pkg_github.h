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

#include <string.h>
#include <stdbool.h>
#include "string_utils.h"

static inline const char* c4pkg_github_repo_name(const char *repo)
{
  if (!repo) {
    return NULL;
  }
  
  const char *name = strrchr(repo, '/');
  return name ? name + 1 : repo;
}

static inline char* c4pkg_github_pkgurl(const char *repo)
{
  return repo ? string_concat("https://raw.githubusercontent.com/", repo, "/master/", c4pkg_github_repo_name(repo), ".zip", NULL) : NULL;
}

bool c4pkg_github_download(const char *repo);
