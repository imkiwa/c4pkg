#include <stdio.h>
#include <string.h>

#include "c4pkg.h"

void print_info(package_t pkg)
{
  pkginfo_t i = package_get_info(pkg);
  
  printf("=> Package Query\n");
  printf(" package: %s\n", i->p_name);
  printf(" description: %s\n", i->p_desc);
  printf(" version: %d.%d.%d\n", i->p_major, i->p_minor, i->p_patch);
  
  if (i->p_deps) {
    printf("=> Package Dependencies\n");
    for (int n=0; n<i->p_dep_count; ++n) {
      pkginfo_t d = i->p_deps[n];
      printf(" #%-2d %s(%d.%d.%d)\n", n, d->p_name, d->p_major, d->p_minor, d->p_patch);
    }
  }
  
  if (i->p_files) {
    printf("=> Package Files\n");
    for (int n=0; n<i->p_file_count; ++n) {
      printf(" %s\n", i->p_files[n]);
    }
  }
}

int main(int argc, char **argv)
{
  if (argc == 1) {
    return 0;
  }
  
  if (strcmp("-Q", argv[1]) == 0) {
    package_t pkg = c4pkg_query(argv[2], QUERY_ALL);
    if (!pkg) {
      printf("Failed to query %s: %s\n", argv[2], query_get_error());
      return 1;
    }
    
    print_info(pkg);
    package_close(pkg);
    return 0;
  
  } else if (strcmp("-R", argv[1]) == 0) {
    return c4pkg_remove(argv[2]) ? 0 : 1;
  }
  
  return c4pkg_install_file(argv[1]);
}
