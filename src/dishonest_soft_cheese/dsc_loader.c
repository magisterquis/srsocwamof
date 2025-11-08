/*
 * dsc_loader.c
 * Load dishonest_soft_cheese.so
 * By J. Stuart McMurray
 * Created 20251031
 * Last Modified 20251031
 */

#include <dlfcn.h>
#include <err.h>
#include <stddef.h>

int
main(void)
{
        /* Load the library. */
        if (NULL == dlopen("./dishonest_soft_cheese.so", RTLD_NOW))
                errx(10, "dlopen: %s", dlerror());

        return 0;
}

