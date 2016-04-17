#pragma once

#include <stdbool.h>

typedef struct c4pkg_net_callback_table_s callback_table_t;
struct c4pkg_net_callback_table_s
{
  int (*print)(const char*, ...);
  
  /**
   * void notify(void *userdata, double total, double wrote);
   */
  void (*notify)(void*, double, double);
  
  /**
   * void start(void *userdata);
   */
  void (*start)(void*);
};


bool c4pkg_net_download(const char *file, const char *url, callback_table_t *callbacks, void *userdata, long timeout, bool progress, bool force_restart);

void c4pkg_net_print_progress(const char *tag, double total, double wrote);
