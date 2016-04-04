#pragma once

#define C4PKG_MANIFEST_NAME "package"
#define C4PKG_MANIFEST_DESC "description"
#define C4PKG_MANIFEST_MAJOR "major-version"
#define C4PKG_MANIFEST_MINOR "minor-version"
#define C4PKG_MANIFEST_PATCH "patch-version"

pkginfo_t pkginfo_parse_buffer(const char *buffer);

pkginfo_t pkginfo_parse_file(const char *path);

pkginfo_t pkginfo_parse_fp(FILE *fp);

pkginfo_t pkginfo_parse_fd(int fd);

void pkginfo_delete(pkginfo_t info);

const char* pkginfo_get_error();
