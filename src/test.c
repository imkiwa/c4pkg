#include <stdio.h>

#include "c4pkg.h"
#include "c4pkg_net.h"

void test(const char *url)
{
  if (!url) {
    return;
  }
  
  char *fname = strrchr(url, '/') + 1;
  
  callback_table_t cbs = {
    .print = printf,
    .notify = NULL
  };
  
  c4pkg_net_download(fname, url, &cbs, NULL, 5, true, true);
}
