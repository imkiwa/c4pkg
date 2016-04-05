#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <limits.h>

#include "fs_utils.h"

bool mkdir_recursive(const char *cpath, mode_t mode)
{
  char *path = strdup(cpath);
  if (!path) {
    return false;
  }
  
  char currpath[PATH_MAX];
  char *pathpiece;
  
  struct stat st;
  strcpy(currpath, "");
  pathpiece = strtok(path, "/");
  
  if (path[0] == '/') {
    strcat(currpath, "/");
  }
  
  while (pathpiece != NULL) {
    if (strlen(currpath) + strlen(pathpiece) + 2 > PATH_MAX) {
      free(path);
      return false;
    }
    
    strcat(currpath, pathpiece);
    strcat(currpath, "/");
    
    if (stat(currpath, &st) != 0) {
      if (mkdir(currpath, mode) < 0) {
        free(path);
        return false;
      }
    }
  
    pathpiece = strtok(NULL, "/");
  }
  
  free(path);
  return true;
}
