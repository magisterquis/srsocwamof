# Makefile
# Build the_c_api things
# By J. Stuart McMurray
# Created 20251028
# Last Modified 20251102

ALL    = loader print_maps.so print_maps_sneakily_remapped.so
CFLAGS = -Wall -Werror -Wextra --pedantic -O2

all: ${ALL}
.PHONY: all

loader: loader.c
	${CC} ${CFLAGS} -o $@ $>

print_maps.so: print_maps.c
	${CC} ${CFLAGS} -fPIC -shared -o $@ $>

print_maps_sneakily_remapped.so: print_maps_sneakily_remapped.c
print_maps_sneakily_remapped.so: sneaky_remap.c sneaky_remap.h
	${CC} ${CFLAGS} -DSREM_DEBUG -fPIC -shared -o $@ ${>:M*.c}

sneaky_remap.c sneaky_remap.h:
	curl -LO https://raw.githubusercontent.com/magisterquis/sneaky_remap/refs/heads/master/$@

clean:
	rm -f ${ALL} sneaky_remap.c sneaky_remap.h strace.out
.PHONY: clean
