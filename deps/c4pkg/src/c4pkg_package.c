#include "c4pkg.h"

/**
 * Open a package from path,
 * return NULL if something	 goes wrong.
 */
package_t package_open_file(const char *path);


/**
 * Open a package from opened FILE,
 * return NULL if something	 goes wrong.
 */
package_t package_open_fp(FILE *fp);


/**
 * Open a package from opened fd,
 * return NULL if something	 goes wrong.
 */
package_t package_open_fd(int fd);


/**
 * Close and release package.
 */
void package_close(package_t pkg);

