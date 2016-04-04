#include <fcntl.h>
#include <unistd.h>
#include <malloc.h>
#include <stdarg.h>

#include "c4pkg.h"
#include "buffer_utils.h"
#include "cJSON.h"

static char error_buffer[1024] = {0};

static void pkginfo_set_error(const char *fmt, ...)
{
  va_list arg;
  va_start(arg, fmt);
  vsnprintf(error_buffer, sizeof(error_buffer), fmt, arg);
  va_end(arg);
}

static pkginfo_t pkginfo_new()
{
  return (pkginfo_t) malloc(sizeof(struct c4pkg_package_info_s));
}

pkginfo_t pkginfo_parse_buffer(const char *buffer)
{
  cJSON *root = cJSON_Parse(buffer);
  if (!root) {
    pkginfo_set_error("Failed to parse manifest: %s", cJSON_GetErrorPtr());
    goto fail;
  }
  
  pkginfo_t info = pkginfo_new();
  if (!info) {
    pkginfo_set_error("Failed to allocate memory");
    goto fail;
  }
  
  info->installed = false;
  
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
  
  cJSON_Delete(root);
  return info;

fail:
  if (root) {
    cJSON_Delete(root);
  }
  if (info) {
    pkginfo_delete(info);
  }
  
  return NULL;
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
  
  free(info);
}

const char* pkginfo_get_error()
{
  return error_buffer;
}

