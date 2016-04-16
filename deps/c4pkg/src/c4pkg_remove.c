#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

#include "c4pkg_remove.h"
#include "c4pkg_query.h"
#include "c4pkg_list.h"
#include "fs_utils.h"
#include "string_utils.h"

ERROR_BUFFER(remove);

static bool c4pkg_remove_package_files(pkginfo_t info)
{
  const char *p = NULL;
  
  for (int i=0; i<info->p_file_count; ++i) {
    p = info->p_files[i];
    if (!p) {
      continue;
    }
    
    char *full = string_concat(C4PKG_PKG_PATH, "/", p, NULL);
    if (!full) {
      return false;
    }
    
    unlink(full);
  }
  return true;
}

bool c4pkg_remove(const char *name)
{
  if (!name) {
    return false;
  }
  
  char *list_dir = c4pkg_get_list_dir(name);
  if (!list_dir) {
    remove_set_error("Failed to get list dir");
    printf("%s\n", remove_get_error());
    return false;
  }
  
  package_t pkg = c4pkg_query(name, QUERY_ALL);
  if (!pkg) {
    remove_set_error("Package '%s' is not installed", name);
    printf("%s\n", remove_get_error());
    goto fail;
  }
  
  pkginfo_t info = package_get_info(pkg);
  if (info->p_files && info->p_file_count > 0) {
    if (!c4pkg_remove_package_files(info)) {
      printf("%s\n", remove_get_error());
      goto fail;
    }
  }
  
  if (!unlink_recursive(list_dir, true)) {
    remove_set_error("Failed to remove list dir");
    printf("%s\n", remove_get_error());
    goto fail;
  }
  
  printf("=> Package '%s' was successfully removed\n", name);
  
  free(list_dir);
  package_close(pkg);
  return true;

fail:
  free(list_dir);
  package_close(pkg);
  return false;
}
