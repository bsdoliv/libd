.include "Makefile.inc"

distrib: .PHONY
	mkdir -p ${BINDIR} ${LIBDIR} ${INCLUDEDIR}

distclean clean: .PHONY
	rm -rfv ${BINDIR} ${LIBDIR} ${INCLUDEDIR} ${DEST_DIR}

install: .PHONY distrib

.ifnmake regress
SUBDIR= contrib/libuv src/corelib
.include <bsd.subdir.mk>
.endif

regress: .PHONY 
	${.MAKE} distrib all install

# vim: set ft=make ts=8 sw=8 noet:
