#include <stdio.h>
#include <string.h>

#include "c4pkg.h"

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
    
    c4pkg_print_package_info(pkg);
    package_close(pkg);
    return 0;
  
  } else if (strcmp("-R", argv[1]) == 0) {
    return c4pkg_remove(argv[2]) ? 0 : 1;
  }
  
  return c4pkg_install_file(argv[1]);
}
