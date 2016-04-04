#include <fcntl.h>
#include <unistd.h>
#include <malloc.h>
#include <stdarg.h>

#include "c4pkg.h"
#include "buffer_utils.h"
#include "cJSON.h"

ERROR_BUFFER(pkginfo);

static pkginfo_t pkginfo_new()
{
  pkginfo_t i = (pkginfo_t) malloc(sizeof(struct c4pkg_package_info_s));
  if (!i) {
    return NULL;
  }
  
  memset(i, '\0', sizeof(struct c4pkg_package_info_s));
  return i;
}

static pkginfo_t pkginfo_parse_internal(cJSON *root, bool check_deps)
{
  if (!root) {
    return NULL;
  }
  
  pkginfo_t info = pkginfo_new();
  if (!info) {
    pkginfo_set_error("Internal Error: Failed to allocate memory for package.");
    goto fail;
  }
  
  // reusable pointer.
  cJSON *node = NULL;
  
  // read package's primary info: name
  node = cJSON_GetObjectItem(root, C4PKG_MANIFEST_NAME);
  if (!node || node->type != cJSON_String) {
    pkginfo_set_error("No '" C4PKG_MANIFEST_NAME "' was found in manifest or it's not a string value!");
    goto fail;
  }
  
  info->p_name = strdup(node->valuestring);
  info->p_name_length = strlen(info->p_name);
  if (!info->p_name || info->p_name_length == 0) {
    pkginfo_set_error("Internal Error: Failed to copy value of '" C4PKG_MANIFEST_NAME "' to pkginfo_t.");
    goto fail;
  }
  // Don't free(node);
  // It will be released automatically in cJSON_Delete(root);
  
  
  // read package's primary info: description
  node = cJSON_GetObjectItem(root, C4PKG_MANIFEST_DESC);
  if (node && node->type == cJSON_String) {
    info->p_desc = strdup(node->valuestring);
    info->p_desc_length = strlen(info->p_desc);
    
    if (!info->p_desc || info->p_desc_length == 0) {
      pkginfo_set_error("Internal Error: Failed to copy value of '" C4PKG_MANIFEST_DESC "' to pkginfo_t.");
      goto fail;
    }
  }
  
  // read major version
  node = cJSON_GetObjectItem(root, C4PKG_MANIFEST_MAJOR);
  if (!node || node->type != cJSON_Number) {
    pkginfo_set_error("No '" C4PKG_MANIFEST_MAJOR "' was found in manifest or it's not a integer value!");
    goto fail;
  }
  
  info->p_major = node->valueint;
  
  // read minor version
  node = cJSON_GetObjectItem(root, C4PKG_MANIFEST_MINOR);
  if (!node || node->type != cJSON_Number) {
    pkginfo_set_error("No '" C4PKG_MANIFEST_MINOR "' was found in manifest or it's not a integer value!");
    goto fail;
  }
  
  info->p_minor = node->valueint;
  
  // read patch version
  node = cJSON_GetObjectItem(root, C4PKG_MANIFEST_PATCH);
  if (!node || node->type != cJSON_Number) {
    pkginfo_set_error("No '" C4PKG_MANIFEST_PATCH "' was found in manifest or it's not a integer value!");
    goto fail;
  }
  
  info->p_patch = node->valueint;
  
  // read dependencies
  if (check_deps 
   && (node = cJSON_GetObjectItem(root, C4PKG_MANIFEST_DEPS))
   && node->type == cJSON_Array
   && (info->p_dep_count = cJSON_GetArraySize(node)) > 0) {
    
    // allocate memory for dependencies
    info->p_deps = (pkginfo_t*) malloc(sizeof(pkginfo_t) * info->p_dep_count);
    
    if (!info->p_deps) {
      pkginfo_set_error("Internal Error: Failed to allocate memory for dependencies.");
      goto fail;
    }
    
    memset(info->p_deps, '\0', sizeof(struct c4pkg_package_info_s) * info->p_dep_count);
    
    cJSON *dep = NULL;
    for (int i=0; i<info->p_dep_count; ++i) {
      dep = cJSON_GetArrayItem(node, i);
      if (!dep) {
        pkginfo_set_error("Failed to get json string for dependence #%d", i);
        goto fail;
      }
      
      // No need to check dependencies' dependencies
      info->p_deps[i] = pkginfo_parse_internal(dep, false);
      if (!info->p_deps[i]) {
        pkginfo_set_error("Failed to parse info for dependence #%d", i);
        goto fail;
      }
    }
  }
  
  /////
  return info;

fail:
  if (info) {
    pkginfo_delete(info);
  }
  
  return NULL;
}

pkginfo_t pkginfo_parse_buffer(const char *buffer)
{
  cJSON *root = cJSON_Parse(buffer);
  if (!root) {
    pkginfo_set_error("Failed to parse manifest: %s", cJSON_GetErrorPtr());
    return NULL;
  }
  
  pkginfo_t info = pkginfo_parse_internal(root, true);
  
  cJSON_Delete(root);
  return info;
}

pkginfo_t pkginfo_parse_file(const char *path)
{
  if (!path) {
    return NULL;
  }
  
  return pkginfo_parse_fd(open(path, O_RDONLY));
}

pkginfo_t pkginfo_parse_fp(FILE *fp)
{
  if (!fp) {
    return NULL;
  }
  
  return pkginfo_parse_fd(fileno(fp));
}

pkginfo_t pkginfo_parse_fd(int fd)
{
  char *buffer = buffer_readall_fd(fd, NULL);
  if (!buffer) {
    return NULL;
  }
  
  pkginfo_t info = pkginfo_parse_buffer(buffer);
  if (!info) {
    return NULL;
  }
  
  free(buffer);
  return info;
}

void pkginfo_delete(pkginfo_t info)
{
  if (!info) {
    return;
  }
  
  if (info->p_name && info->p_name_length > 0) {
    free(info->p_name);
  }
  
  if (info->p_desc && info->p_desc_length > 0) {
    free(info->p_desc);
  }
  
  if (info->p_deps) {
    for (int i=0; i<info->p_dep_count; ++i) {
      pkginfo_delete(info->p_deps[i]);
    }
  }
  
  free(info);
}
