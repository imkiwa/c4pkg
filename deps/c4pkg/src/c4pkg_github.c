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


#include <errno.h>
#include <string.h>

#include "c4pkg_github.h"
#include "c4pkg_package.h"
#include "string_utils.h"
#include "fs_utils.h"

ERROR_BUFFER(gitdl);

char* c4pkg_github_download(const char *repo)
{
  if (!repo) {
    return NULL;
  }
  
  static callback_table_t cbtable = {
    .print = printf,
    .notify = NULL,
    .start = NULL
  };
  
  char *save = NULL;
  char *url = c4pkg_github_get_package_url(repo);
  if (!url) {
    gitdl_set_error("Failed to get package url");
    return NULL;
  }
  
  const char *basename = c4pkg_net_extract_file_from_url(url);
  if (!basename) {
    gitdl_set_error("Failed to extract file name from url");
    goto fail;
  }
  
  save = string_concat(C4PKG_TMP_PATH, "/", basename, NULL);
  if (!save) {
    gitdl_set_error("Internal Error: Failed to generate tmp file path");
    goto fail;
  }
  
  if (!mkdir_parent(save, 0755)) {
    gitdl_set_error("Failed to mkdir for %s: %s", save, strerror(errno));
    goto fail;
  }
  
  if (!c4pkg_net_download(save, url, &cbtable, NULL, 10, true, false)) {
    gitdl_set_error("Failed to download package");
    goto fail;
  }
  
  return save;

fail:
  free(url);
  if (save) {
    free(save);
  }
  return NULL;
}
