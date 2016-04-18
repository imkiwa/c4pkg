/**
 * Copyright (C) 2016  apollo-opensource
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */


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
