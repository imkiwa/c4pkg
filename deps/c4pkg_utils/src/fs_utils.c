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
  
  char *item = NULL;
  while ((e = readdir(dir)) != NULL) {
    if (!strcmp(e->d_name, ".") || !strcmp(e->d_name, "..")) {
      continue;
    }
    
    item = string_concat(path, "/", e->d_name, NULL);
    if (!item) {
      goto fail;
    }
    
    if (e->d_type == DT_REG) {
      if (chmod(item, mode) != 0) {
        goto fail;
      }
    
    } else if (e->d_type == DT_DIR) {
      if (chmod_recursive(item, mode, true) != 0) {
        goto fail;
      }
    }
    
    free(item);
    item = NULL;
  }
  
  closedir(dir);
  return true;

fail:
  if (item) {
    free(item);
  }
  closedir(dir);
  return false;
}

bool unlink_recursive(const char *path, bool include_self)
{
  if (!path) {
    return false;
  }
  
  DIR *dir;
  struct dirent *e;
  dir = opendir(path);
  if (!dir) {
    return false;
  }
  
  char *item = NULL;
  while ((e = readdir(dir)) != NULL) {
    if (!strcmp(e->d_name, ".") || !strcmp(e->d_name, "..")) {
      continue;
    }
    
    item = string_concat(path, "/", e->d_name, NULL);
    if (!item) {
      goto fail;
    }
    
    if (e->d_type == DT_REG) {
      if (unlink(item) != 0) {
        goto fail;
      }
    
    } else if (e->d_type == DT_DIR) {
      if (unlink_recursive(item, true) != 0) {
        goto fail;
      }
    }
    
    free(item);
    item = NULL;
  }
  
  closedir(dir);
  
  if (include_self && rmdir(path) != 0) {
    return false;
  }
  
  return true;

fail:
  if (item) {
    free(item);
  }
  closedir(dir);
  return false;
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
