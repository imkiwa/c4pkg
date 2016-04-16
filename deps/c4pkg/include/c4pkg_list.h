#pragma once

#include <stdio.h>
#include <stdbool.h>

#include "c4pkg_config.h"
#include "c4pkg_install.h"
#include "c4pkg_package.h"

char* c4pkg_get_list_dir(const char *name);

char* c4pkg_get_list_file(const char *name);

char* c4pkg_get_manifest_file(const char *name);

bool c4pkg_list_dump_file(FILE *to, package_t pkg);

bool c4pkg_list_read_file(FILE *from, package_t pkg);
