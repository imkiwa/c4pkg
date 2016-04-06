#include "c4pkg.h"
#include "string_utils.h"

char* c4pkg_get_list_dir(const char *name)
{
  if (!name) {
    return NULL;
  }
  
  return string_concat(C4PKG_LIST_PATH, "/", name, NULL);
}

char* c4pkg_get_list_file(const char *name)
{
  if (!name) {
    return NULL;
  }
  
  return string_concat(C4PKG_LIST_PATH, "/", name, "/", C4PKG_LIST_FILE, NULL);
}

char* c4pkg_get_manifest_file(const char *name)
{
  if (!name) {
    return NULL;
  }
  
  return string_concat(C4PKG_LIST_PATH, "/", name, "/", C4PKG_MANIFEST, NULL);
}

bool c4pkg_list_dump_file(FILE *to, package_t pkg)
{
  if (!to) {
    return false;
  }
  
  pkginfo_t i = package_get_info(pkg);
  for (int n=0; n<i->p_file_count; ++n) {
    if (i->p_files[n]) {
      fprintf(to, "%s\n", i->p_files[n]);
    }
  }
  
  return true;
}
