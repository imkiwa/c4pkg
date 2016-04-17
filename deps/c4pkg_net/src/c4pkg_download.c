#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>

#include "c4pkg_net.h"
#include "curl/curl.h"

typedef struct c4pkg_net_extra_s extra_t;
struct c4pkg_net_extra_s
{
  FILE *file;
  const char *path;
  void *userdata;
  callback_table_t *f;
};

static size_t c4pkg_net_get_content_length(void *data, size_t size, size_t nmemb, void *userdata)
{
  long len = 0;
  if (sscanf(data, "Content-Length: %ld\n", &len) > 0) {
    *((long*) userdata) = len;
  }
  
  return size * nmemb;
}

static size_t c4pkg_net_callback_write(void *ptr, size_t size, size_t nmemb, void *userdata)
{
  extra_t *ext = (extra_t*) userdata;
  return fwrite(ptr, size, nmemb, ext->file);
}

static int c4pkg_net_callback_progress(void *userdata, double total, double wrote, double utotal, double uwrote)
{
  extra_t *ext = (extra_t*) userdata;
  
  if (ext->f->notify) {
    ext->f->notify(ext->userdata, total, wrote);
  } else {
    c4pkg_net_print_progress(ext->path, total, wrote);
  }
  
  return 0;
}

void c4pkg_net_print_progress(const char *tag, double total, double wrote)
{
  double percent = wrote / total * 100;
  printf("\r  %s [%.0lf%%] [%.0lf/%.0lf]\r", tag ? tag : "", percent, wrote, total);
  fflush(stdout);
}

bool c4pkg_net_download(const char *file, const char *url, callback_table_t *callbacks, void *userdata, long timeout, bool progress, bool force_restart)
{
  if (!file || !url || !callbacks) {
    return false;
  }
  
  FILE *fp = NULL;
  curl_off_t start_pos = 0;
  long file_length = 0;
  bool resume = false;
  
  CURL *curl = curl_easy_init();
  if (!curl) {
    return false;
  }
  
  const char *mode = "w";
  if (!force_restart) {
    struct stat buf;
    if (stat(file, &buf) == 0) {
      resume = true;
      start_pos = buf.st_size;
      mode = "ab+";
    }
  }
  
  fp =fopen(file, mode);
  if (!fp) {
    goto fail;
  }
  
  const char *basename = strrchr(file, '/');
  extra_t ext;
  ext.file = fp;
  ext.path = basename ? basename + 1: file;
  ext.userdata = userdata;
  ext.f = callbacks;
  
  // Common
  curl_easy_setopt(curl, CURLOPT_URL, url);
  curl_easy_setopt(curl, CURLOPT_CONNECTTIMEOUT, timeout);
  
  // Don't check https certificate
  curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
  curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);
  
  // Resume from break point
  curl_easy_setopt(curl, CURLOPT_HEADERDATA, &file_length);
  curl_easy_setopt(curl, CURLOPT_HEADERFUNCTION, c4pkg_net_get_content_length);
  curl_easy_setopt(curl, CURLOPT_RESUME_FROM_LARGE, resume ? start_pos: 0);
  
  // Write function
  curl_easy_setopt(curl, CURLOPT_WRITEDATA, &ext);
  curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, c4pkg_net_callback_write);
  
  // Progress bar
  if (progress) {
    curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 0L);
    curl_easy_setopt(curl, CURLOPT_PROGRESSDATA, &ext);
    curl_easy_setopt(curl, CURLOPT_PROGRESSFUNCTION, c4pkg_net_callback_progress);
  } else {
    curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 1L);
  }
  
  // Perform request
  if (ext.f->start) {
    ext.f->start(ext.userdata);
  }
  
  CURLcode ret = 0;
  if ((ret = curl_easy_perform(curl)) != 0) {
    ext.f->print("\nDownload failed: %s\n", curl_easy_strerror(ret));
    goto fail;
  }
  
  ext.f->print("\n");
  
  curl_easy_cleanup(curl);
  fclose(fp);
  return true;

fail:
  curl_easy_cleanup(curl);
  if (fp) {
    fclose(fp);
  }
  return false;
}
