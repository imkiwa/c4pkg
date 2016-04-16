#include "c4pkg_query.h"
#include "c4pkg_list.h"

#include "private/package.h"

ERROR_BUFFER(query);

package_t c4pkg_query(const char *name, int flags)
{
  if (!name) {
    return NULL;
  }
  
  char *mani_path = c4pkg_get_manifest_file(name);
  char *list_path = c4pkg_get_list_file(name);
  
  if (!list_path || !mani_path) {
    query_set_error("Internal Error: Failed to get package info file");
    return NULL;
  }
  
  package_t pkg = package_new();
  if (!pkg) {
    query_set_error("Internal Error: Failed to allocated memory");
    return NULL;
  }
  
  if (flags & QUERY_MANIFEST) {
    pkg->p_info = pkginfo_parse_file(mani_path);
    if (!pkg->p_info) {
      query_set_error("%s", pkginfo_get_error());
      goto fail;
    }
  }
  
  if (flags & QUERY_FILES) {
    FILE *fp = fopen(list_path, "r");
    if (!fp) {
      query_set_error("Failed to open list file '%s'", list_path);
      goto fail;
    }
    
    if (!c4pkg_list_read_file(fp, pkg)) {
      query_set_error("Failed to read List file");
      fclose(fp);
      goto fail;
    }
    
    fclose(fp);
  }
  
  return pkg;
  
fail:
  package_close(pkg);
  return NULL;
}
