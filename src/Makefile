# Makefile
# Build things, for testing
# By J. Stuart McMurray
# Created 20251028
# Last Modified 20251101

SUBDIRS = dishonest_soft_cheese horizontal_aubergine\
	  horizontal_aubergine_sneakily_remapped the_c_api

all: subdirs
.PHONY: all

clean: subdirs
.PHONY: clean

subdirs: .USE
.for SUBDIR in ${SUBDIRS}
	${MAKE} -C ${SUBDIR} $@
.endfor
