.include <bsd.own.mk>
.include "../Makefile.inc"
.include "${ABSTOP}/mk/cpp.mk"

FILES= 			libuv.a
FILESMODE_libuv.a= 	600
FILESDIR_libuv.a=	${LIBDIR}

FILES+=			include/uv.h
FILESDIR_include/uv.h= 	${INCLUDEDIR}/libuv

FILES+=			include/uv-private/tree.h \
			include/uv-private/uv-bsd.h \
			include/uv-private/uv-darwin.h \
			include/uv-private/uv-linux.h \
			include/uv-private/uv-sunos.h \
			include/uv-private/uv-unix.h
FILESDIR= 	${INCLUDEDIR}/libuv/uv-private

build: .PHONY all

all distclean clean: .PHONY
	${GMAKE} -f ${.CURDIR}/GNUmakefile ${.TARGET}

cleandir: .PHONY
	${GMAKE} -f ${.CURDIR}/GNUmakefile distclean

.include <bsd.files.mk>

# vim: set ft=make ts=8 sw=8 noet:
