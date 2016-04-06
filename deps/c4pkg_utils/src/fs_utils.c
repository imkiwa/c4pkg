#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <limits.h>

#include "fs_utils.h"
#include "string_utils.h"

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

bool chmod_recursive(const char *path, mode_t mode, bool include_self)
{
  if (!path) {
    return false;
  }
  
  if (include_self && chmod(path, mode) != 0) {
    return false;
  }
  
  DIR *dir;
  struct dirent *e;
  dir = opendir(path);
  if (!dir) {
    return false;
  }
  
  while ((e = readdir(dir)) != NULL) {
    if (e->d_type == DT_REG) {
      if (chmod(e->d_name, mode) != 0) {
        closedir(dir);
        return false;
      }
    
    } else if (e->d_type == DT_DIR) {
      if (!strcmp(e->d_name, ".") || !strcmp(e->d_name, "..")) {
        continue;
      }
      
      char *next = string_concat(path, "/", e->d_name, NULL);
      if (!next) {
        closedir(dir);
        return false;
      }
      
      int ret = chmod_recursive(next, mode, true);
      free(next);
      if (ret != 0) {
        closedir(dir);
        return false;
      }
    } // DT_DIR
  } // while
  
  closedir(dir);
  return true;
}

bool mkdir_parent(const char *cpath, mode_t mode)
{
  if (!cpath) {
    return false;
  }
  
  char *path = strdup(cpath);
  if (!path) {
    return false;
  }
  
  char *slash = strrchr(path, '/');
  if (!slash) {
    free(path);
    return false;
  }
  
  // split path and file name
  *slash = '\0';
  
  // create parent directory
  bool ret = mkdir_recursive(path, mode);
  
  free(path);
  return ret;
}
