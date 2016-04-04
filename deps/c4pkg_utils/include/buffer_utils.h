#pragma once

#include <unistd.h>
#include <fcntl.h>
#include <malloc.h>
#include <stdio.h>

char* buffer_readall_fd(int fd, ssize_t *psz);
