#pragma once

#include <stdarg.h>

#define ERROR_BUFFER_DEF(prefix) \
  const char* prefix##_get_error()

#define ERROR_BUFFER(prefix) \
  static char prefix##_error_buffer[128]; \
  static void prefix##_set_error(const char *fmt, ...) \
  { \
    va_list arg; \
    va_start(arg, fmt); \
    vsnprintf(prefix##_error_buffer, sizeof(prefix##_error_buffer), fmt, arg); \
    va_end(arg); \
  } \
  \
  ERROR_BUFFER_DEF(prefix) \
  { \
    return prefix##_error_buffer; \
  }
