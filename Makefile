.include "Makefile.inc"

distrib: .PHONY
	mkdir -p ${BINDIR} ${LIBDIR} ${INCLUDEDIR} ${INCLUDEDIR}/qt

distclean clean: .PHONY
	rm -rfv ${BINDIR} ${LIBDIR} ${INCLUDEDIR} ${DEST_DIR}
	cd ${.CURDIR}/contrib/libuv && ${.MAKE} ${.TARGET}
	cd ${.CURDIR}/contrib/qtbase && ${.MAKE} ${.TARGET}
	cd ${.CURDIR}/src/corelib && ${.MAKE} ${.TARGET}


regress: .PHONY distrib
	cd ${.CURDIR}/contrib/libuv && ${.MAKE} build install
	cd ${.CURDIR}/contrib/qtbase && ${.MAKE} build install
	cd ${.CURDIR}/src/corelib && ${.MAKE} build install

# vim: set ft=make ts=8 sw=8 noet:
