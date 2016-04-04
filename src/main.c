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
  zipfile_t zip = zip_open_file(argv[1]);
  if (!zip) {
    printf("Error: zip_open_file\n");
    return 0;
  }
  
  zipentry_t e = zip_lookup(zip, "manifest.json");
  if (!e) {
    printf("Error: zip_lookup\n");
    zip_close(zip);
    return 0;
  }
  
  size_t sz = zipentry_get_size(e);
  char *buffer = (char*) malloc(sz+1);
  zipentry_decompress(e, buffer, sz);
  buffer[sz] = '\0';
  
  pkginfo_t i = pkginfo_parse_buffer(buffer);
  free(buffer);
  
  if (!i) {
    printf("Error: pkginfo_parse_buffer: %s\n", pkginfo_get_error());
    zip_close(zip);
    return 0;
  }
  
  print_info(i);
  for (int n=0; n<i->p_dep_count; ++n) {
    printf("=======\n");
    print_info(i->p_deps[n]);
  }
  
  pkginfo_delete(i);
  zip_close(zip);
  return 0;
}
