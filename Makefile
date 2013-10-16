.include "Makefile.inc"

distrib: .PHONY
	mkdir -p ${BINDIR} ${LIBDIR} ${INCLUDEDIR} ${INCLUDEDIR}/libuv/uv-private

distclean clean: .PHONY
	rm -rfv ${BINDIR} ${LIBDIR} ${INCLUDEDIR}

install: distrib

SUBDIR= contrib/libuv src/corelib
.include <bsd.subdir.mk>

# vim: set ft=make ts=8 sw=8 noet:
