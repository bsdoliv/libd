.include <bsd.own.mk>
.include "../Makefile.inc"
.include "${ABSTOP}/mk/cpp.mk"

FILES= 			libuv.a
FILESMODE_libuv.a= 	600
FILESDIR_libuv.a=	${LIBDIR}
FILESNAME_libuv.a !=	id -u -n

build: .PHONY all

all distclean clean: .PHONY
	${GMAKE} -f ${.CURDIR}/GNUmakefile ${.TARGET}

cleandir: .PHONY
	${GMAKE} -f ${.CURDIR}/GNUmakefile distclean

.include <bsd.files.mk>

# vim: set ft=make ts=8 sw=8 noet:
