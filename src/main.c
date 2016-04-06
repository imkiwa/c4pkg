#include <stdio.h>
#include <string.h>

#include "c4pkg.h"

int main(int argc, char **argv)
{
  if (argc == 1) {
    return 0;
  }
  
  if (strcmp(argv[1], "--flags") == 0) {
    c4pkg_build_flags();
    return 0;
  }
  
  return c4pkg_install_file(argv[1]);
}
