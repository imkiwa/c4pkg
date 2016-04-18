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

#include "c4pkg_net.h"
#include "string_utils.h"
#include "error_utils.h"

ERROR_BUFFER_DEF(gitdl);

static inline const char* c4pkg_github_repo_name(const char *repo)
{
  const char *name = c4pkg_net_extract_file_from_url(repo);
  return name ? name : repo;
}

static inline char* c4pkg_github_get_package_url(const char *repo)
{
  return repo ? string_concat("https://raw.githubusercontent.com/", repo, "/master/pkgfiles/", c4pkg_github_repo_name(repo), ".zip", NULL) : NULL;
}

char* c4pkg_github_download(const char *repo);
