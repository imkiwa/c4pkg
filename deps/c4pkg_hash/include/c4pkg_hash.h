#pragma once

#include <stdint.h>

uint8_t* c4pkg_hash_sha1(char *data, int len, int *retsz);

char* c4pkg_hash_sha1_string(char *data, int len);

char* c4pkg_hash_to_string(uint8_t *digest, int len);
