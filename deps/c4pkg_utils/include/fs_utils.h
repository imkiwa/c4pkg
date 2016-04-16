#pragma once

#include <stdbool.h>
#include <unistd.h>

bool mkdir_recursive(const char *path, mode_t mode);

bool chmod_recursive(const char *path, mode_t mode, bool include_self);

bool unlink_recursive(const char *path, bool include_self);

bool mkdir_parent(const char *path, mode_t mode);
