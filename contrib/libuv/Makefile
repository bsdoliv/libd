.include <bsd.own.mk>
.include "../Makefile.inc"
.include "${ABSTOP}/mk/cpp.mk"

LDSTATIC=	-static
LIB=		uv

cleandir: .PHONY
	${GMAKE} -f ${.CURDIR}/GNUmakefile distclean

.include <bsd.lib.mk>

all build distclean clean: .PHONY
	${GMAKE} -f ${.CURDIR}/GNUmakefile ${.TARGET}

# vim: set ft=make ts=8 sw=8 noet:
