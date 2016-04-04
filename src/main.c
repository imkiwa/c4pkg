#include <stdio.h>

#include "c4pkg.h"

void print_info(pkginfo_t i)
{
  printf("name: %s\n"
         "desc: %s\n"
         "major: %d\n"
         "minor: %d\n"
         "patch: %d\n", 
   i->p_name, i->p_desc,
   i->p_major, i->p_minor, i->p_patch);
}

int main(int argc, char **argv)
{ 
  package_t pkg = package_open_file(argv[1]);
  if (!pkg) {
    printf("package_open_file: %s\n", package_get_error());
    return 0;
  }
  
  pkginfo_t i = package_get_info(pkg);
  
  print_info(i);
  for (int n=0; n<i->p_dep_count; ++n) {
    printf("=======\n");
    print_info(i->p_deps[n]);
  }
  
  package_close(pkg);
  return 0;
}
