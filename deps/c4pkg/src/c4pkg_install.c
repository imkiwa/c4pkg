#include <stdlib.h>
#include <string.h>

#include "c4pkg.h"
#include "buffer_utils.h"
#include "fs_utils.h"
#include "string_utils.h"

#define CALL(fn, arg...) \
  if (fn) { fn(arg); }

#define CALLE(fn) \
  CALL(fn, "%s\n", install_get_error())

ERROR_BUFFER(install);

static void c4pkg_default_opt(inst_opt_t *opt)
{
  opt->o_inst_dir = C4PKG_PKG_PATH;
  opt->o_update_when_exists = true;
  opt->o_ignore_dependencies = false;
  opt->print_fn = printf;
}

static void c4pkg_install_fix_permission()
{
  chmod_recursive(C4PKG_PKG_BIN_PATH, 0755, false);
}

static bool c4pkg_install_dump_pkg_info(package_t pkg, const char *list_path, const char *mani_path)
{
  FILE *lf = fopen(list_path, "w");
  if (!lf) {
    install_set_error("Failed to open '%s'", list_path);
    return false;
  }
  
  FILE *mf = fopen(mani_path, "w");
  if (!mf) {
    install_set_error("Failed to open '%s'", mani_path);
    goto fail;
  }
  
  if (!c4pkg_list_dump_file(lf, pkg)) {
    install_set_error("Failed to dump file list");
    goto fail;
  }
  
  pkginfo_t i = package_get_info(pkg);
  fwrite(i->p_mnfs, i->p_mnfs_length, 1, mf);
  
  fclose(lf);
  fclose(mf);
  return true;
  
fail:
  if (lf) {
    fclose(lf);
  }
  if (mf) {
    fclose(mf);
  }
  return false;
}

static bool c4pkg_install_rollback(package_t pkg)
{
  return true;
}

static bool c4pkg_install_internal(inst_opt_t *opt, package_t pkg, zipfile_t data_zip)
{
  int count = zip_get_entry_count(data_zip);
  if (count <= 0) {
    install_set_error("data.zip is empty");
    goto fail;
  }
  
  pkginfo_t info = package_get_info(pkg);
  info->p_file_count = 0;
  info->p_files = (char**) malloc(sizeof(char*) * count);
  if (!info->p_files) {
    install_set_error("Internal Error: Failed to allocate memory for file list");
    goto fail;
  }
  
  zipentry_t e = NULL;
  int index = 0;
  int sec = 0;
  
  const char *zname = NULL;
  size_t zsz = 0;
  bool write = true;
  
  while (zip_foreach(data_zip, (void**) &e)) {
    zname = zipentry_get_name(e);
    zsz = strlen(zname);
    write = true;
    
    if (zname[zsz - 1] == '/') {
      char *n = string_concat(opt->o_inst_dir, "/", zname, NULL);
      if (!n) {
        install_set_error("Internal Error: Failed to concat string");
        goto rollback;
      }
      
      // If dir already exists
      // we won't write it to list file
      if (access(n, F_OK) == 0) {
        write = false;
      }
      free(n);
    }
    
    if (write) {
      info->p_files[index] = strdup(zname);
      if (!info->p_files[index]) {
        install_set_error("Internal Errno: Failed to copy zip entry name");
        goto rollback;
      }
      index++;
      info->p_file_count++;
    }
    
    if (!zipentry_extract_to(e, opt->o_inst_dir)) {
      install_set_error("Internal Error: Failed to extract '%s'", zname);
      goto rollback;
    }
  }
  
  char *list_dir = c4pkg_get_list_dir(package_get_name(pkg));
  char *list_path = c4pkg_get_list_file(package_get_name(pkg));
  char *mani_path = c4pkg_get_manifest_file(package_get_name(pkg));
  
  if (!list_dir || !list_path || !mani_path) {
    install_set_error("Failed to get package info file");
    goto rollback;
  }
  
  if (!mkdir_recursive(list_dir, 0755)) {
    install_set_error("Failed to mkdir for package info");
    goto rollback_free;
  }
  
  if (!c4pkg_install_dump_pkg_info(pkg, list_path, mani_path)) {
    goto rollback_free;
  }
  
  // set executable permission for binaries
  c4pkg_install_fix_permission();
  
  return true;

rollback_free:
  if (list_path) {
    free(list_path);
  }
  if (list_dir) {
    free(list_dir);
  }
  if (mani_path) {
    free(mani_path);
  }
  
rollback:
  while (!c4pkg_install_rollback(pkg)) {
    if (sec > 300) { // 5 minutes
      fprintf(stderr, "Force exit. You can report this as a bug to me, thanks!\n");
      break;
    }
    
    sec += 10;
    fprintf(stderr, "Rollback failed, retrying in %d seconds. Use Ctrl-C to force exit.\n", sec);
    sleep(sec);
  }

fail:
  return false;
}

bool c4pkg_install_with_opt(inst_opt_t *opt)
{
  if (c4pkg_check_root()) {
    install_set_error("You should not run this program as root.");
    fprintf(stderr, "%s\n", install_get_error());
    return false;
  }
  
  if (!opt || !opt->o_src || !opt->o_inst_dir) {
    return false;
  }
  
  // only support SCHEMA_LOCAL,
  // c4pkg_install_git/file will convert SCHEMA_FILE/GIT to SCHEMA_LOCAL.
  if (opt->o_schema.s_type != SCHEMA_LOCAL) {
    switch (opt->o_schema.s_type) {
      case SCHEMA_GIT:
        return c4pkg_install_git(opt->o_schema.s_url);
      case SCHEMA_FILE:
        return c4pkg_install_file(opt->o_schema.s_url);
    }
    
    return c4pkg_install(opt->o_src);
  }
  
  int (*pfn)(const char*, ...) = opt->print_fn;
  
  if (opt->o_src_length == 0) {
    install_set_error("Invalid length of o_src");
    CALLE(pfn);
    goto fail;
  }
  
  package_t pkg = package_open_buffer(opt->o_src, opt->o_src_length);
  if (!pkg) {
    install_set_error("Failed to open package buffer: %s", package_get_error());
    CALLE(pfn);
    goto fail;
  }
  
  zipentry_t data = zip_lookup(pkg->zip, C4PKG_DATA_ZIP);
  if (!data) {
    install_set_error("No '" C4PKG_DATA_ZIP "' was found in zip file");
    CALLE(pfn);
    goto fail;
  }
  
  size_t sz = zipentry_get_size(data);
  char *buffer = (char*) malloc(sizeof(char) * (sz + 1));
  if (!buffer) {
    install_set_error("Internal Error: Failed to allocate memory for '" C4PKG_DATA_ZIP "'");
    goto fail;
  }
  
  zipentry_decompress(data, buffer, sz);
  buffer[sz] = '\0';
  
  zipfile_t data_zip = zip_open_buffer(buffer, sz);
  if (!data_zip) {
    install_set_error("Failed to open decompressed '" C4PKG_DATA_ZIP "' buffer");
    goto fail;
  }
  
  if (!c4pkg_install_internal(opt, pkg, data_zip)) {
    CALLE(pfn);
    goto fail_close;
  }
  
  printf("=> Package '%s' was successfully installed\n", package_get_name(pkg));
  
  zip_close(data_zip);
  package_close(pkg);
  return true;

fail_close:
  if (data_zip) {
    zip_close(data_zip);
  }
  
fail:
  if (pkg) {
    package_close(pkg);
  }
  return false;
}

bool c4pkg_install(const char *url)
{
  if (!url) {
    return NULL;
  }
  
  schema_t sch;
  if (!c4pkg_schema_parse(url, &sch)) {
    install_set_error("Failed to parse url: %s", url);
    return false;
  }
  
  if (!sch.s_url) {
    install_set_error("Internal Error: Failed to copy string");
    return false;
  }
  
  bool ret = false;
  switch (sch.s_type) {
    case SCHEMA_FILE:
      ret = c4pkg_install_file(sch.s_url);
      break;
    
    case SCHEMA_GIT:
      ret = c4pkg_install_git(sch.s_url);
      break;
    
    default:
      install_set_error("Unsupported schema");
      ret = false;
      break;
  }
  
  free(sch.s_url);
  return ret;
}

bool c4pkg_install_git(const char *repo)
{
  printf("Internal Error: c4pkg_install_git not supported.\n");
  return false;
}

bool c4pkg_install_buffer(const char *buffer, size_t bufsz)
{
  inst_opt_t opt;
  
  c4pkg_default_opt(&opt);
  opt.o_schema.s_type = SCHEMA_LOCAL;
  opt.o_src = buffer;
  opt.o_src_length = bufsz;
  
  c4pkg_install_with_opt(&opt);
}

bool c4pkg_install_file(const char *path)
{
  if (!path) {
    return false;
  }
  
  return c4pkg_install_fd(open(path, O_RDONLY));
}

bool c4pkg_install_fp(FILE *fp)
{
  if (!fp) {
    return false;
  }
  
  return c4pkg_install_fd(fileno(fp));
}

bool c4pkg_install_fd(int fd)
{
  if (fd < 0) {
    return false;
  }
  
  ssize_t sz;
  char *buffer = buffer_readall_fd(fd, &sz);
  if (!buffer) {
    return false;
  }
  
  bool ret = c4pkg_install_buffer(buffer, (size_t) sz);
  
  free(buffer);
  return ret;
}

