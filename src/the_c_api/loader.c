/*
 * loader.c
 * Load a shared object file
 * By J. Stuart McMurray
 * Created 20251028
 * Last Modified 20251104
 */

#include <dlfcn.h>
#include <err.h>
#include <stddef.h>
#include <stdint.h>

typedef int (*maps_printer)(void);

int
main(int argc, char **argv)
{
        maps_printer  print_maps; /* Map-printing function. */
        void         *h;          /* Library handle. */

        /* Make sure we have something to load. */
        if (2 != argc) errx(10, "need a library name");

        /* Load the library. */
        if (NULL == (h = dlopen(argv[1], RTLD_NOW)))
                errx(10, "dlopen: %s", dlerror());

        /* Find and call the function. */
        print_maps = (maps_printer)(uintptr_t)dlsym(h, "print_maps");
        if (NULL == print_maps)
                errx(11, "dlsym (%s): %s", "print_maps", dlerror());

        if (0 != print_maps())
                err(12, "print_maps");
}
