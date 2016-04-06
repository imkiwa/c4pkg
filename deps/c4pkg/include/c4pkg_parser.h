#pragma once

#include "error_utils.h"

#include "c4pkg_config.h"

ERROR_BUFFER_DEF(pkginfo);

pkginfo_t pkginfo_parse_buffer(const char *buffer);

pkginfo_t pkginfo_parse_file(const char *path);

pkginfo_t pkginfo_parse_fp(FILE *fp);

pkginfo_t pkginfo_parse_fd(int fd);

void pkginfo_delete(pkginfo_t info);

const char* pkginfo_get_error();
