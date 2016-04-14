#pragma once

#include <stdbool.h>

#define SCHEMA_LOCAL_STR "local://"
#define SCHEMA_LOCAL_LEN 8

#define SCHEMA_FILE_STR  "file://"
#define SCHEMA_FILE_LEN  7

#define SCHEMA_GIT_STR   "git://"
#define SCHEMA_GIT_LEN   6

typedef struct c4pkg_schema_s schema_t;
typedef enum c4pkg_schema_type_s schtype_t;

enum c4pkg_schema_type_s
{
  SCHEMA_LOCAL = SCHEMA_LOCAL_LEN,
  SCHEMA_FILE  = SCHEMA_FILE_LEN,
  SCHEMA_GIT   = SCHEMA_GIT_LEN
};

struct c4pkg_schema_s
{
  schtype_t s_type;
  char *s_url;
};


bool c4pkg_schema_parse(const char *url, schema_t *schema);
