#include "c4pkg_zip.h"
#include "buffer_utils.h"

zipfile_t zip_open_file(const char *path)
{
  if (!path) {
    return NULL;
  }
  
  return zip_open_fd(open(path, O_RDONLY));
}

zipfile_t zip_open_fp(FILE *fp)
{
  if (!fp) {
    return NULL;
  }
  
  return zip_open_fd(fileno(fp));
}

zipfile_t zip_open_fd(int fd)
{
  ssize_t sz;
  char *buffer = buffer_readall_fd(fd, &sz);
  if (!buffer) {
    return NULL;
  }
  
  zipfile_t info = zip_open_buffer(buffer, (size_t) sz);
  if (!info) {
    return NULL;
  }
  
  free(buffer);
  return info;
}
