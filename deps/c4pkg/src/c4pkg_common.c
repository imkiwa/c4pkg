#include "c4pkg_common.h"

void c4pkg_print_package_info(package_t pkg)
{
  pkginfo_t i = package_get_info(pkg);
  
  printf("=> Package Query\n");
  printf(" package: %s\n", i->p_name);
  printf(" description: %s\n", i->p_desc);
  printf(" version: %d.%d.%d\n", i->p_major, i->p_minor, i->p_patch);
  
  printf("\n");
  printf("=> Package Security\n");
  printf(" checksum: %s\n", i->p_checksum);
  
  if (i->p_deps) {
    printf("\n"); 
    printf("=> Package Dependencies\n");
    for (int n=0; n<i->p_dep_count; ++n) {
      pkginfo_t d = i->p_deps[n];
      printf(" #%-2d %s(%d.%d.%d)\n", n, d->p_name, d->p_major, d->p_minor, d->p_patch);
    }
  }
  
  if (i->p_files) {
    printf("\n");
    printf("=> Package Files\n");
    for (int n=0; n<i->p_file_count; ++n) {
      printf(" %s\n", i->p_files[n]);
    }
  }
}
