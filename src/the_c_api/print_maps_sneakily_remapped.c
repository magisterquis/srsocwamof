/*
 * print_maps_sneakily_remapped.c
 * Library to hide and then print the current process's memory maps
 * By J. Stuart McMurray
 * Created 20251028
 * Last Modified 20251104
 */

#define _GNU_SOURCE

#include <sys/stat.h>

#include <err.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "sneaky_remap.h"

#define BUFLEN (0x1000)

/* ctor runs on library load and prints program's name. */
static void __attribute__((constructor))
ctor(void)
{
        int ret;

        /* Be hidden. */
        switch (ret = sneaky_remap_start(NULL, NULL, 0)) {
                case SREM_RET_OK: /* Good. */
                        break;
                case SREM_RET_ERRNO: /* Not our fault, at least? */
                        warn("sneaky_remap_start");
                        break;
                default:
                        warnx("sneaky_remap error %d", ret);
                        break;
        }

        printf("(ctor) Loaded into %s\n",
                        program_invocation_name);
        fflush(stdout);
}

/* print_maps copies /proc/self/maps to stdout.
 * It returns 0 on success. */
int
print_maps(void)
{
        char    buf[BUFLEN];
        int     fd;
        int     ret;
	ssize_t nw, nr, off;

        fd = ret = -1;

        /* Open the maps file and work out its size. */
        if (-1 == (fd = open("/proc/self/maps", O_RDONLY)))
                goto out;

        /* Copy ALL the bytes! */
        bzero(buf, sizeof(buf));
        while (-1 != (nr = read(fd, buf, sizeof(buf))) && 0 != nr)
                for (off = 0; off < nr; off += nw)
                        if (0 == (nw = write(STDOUT_FILENO, buf + off,
                                                        nr - off)) || -1 == nw)
                                goto out;
        if (-1 == nr)
                goto out;

        /* All is (probably) good. */
        ret = 0;

out:
        if (-1 != fd)
                close(fd);
        return ret;
}
