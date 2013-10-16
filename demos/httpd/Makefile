.include "../Makefile.inc"
.include "${ABSTOP}/mk/cppprog.mk"
.include "${ABSTOP}/mk/libd.mk"

PROG=		httpd
CPPFLAGS+=	-I${INCLUDEDIR}
CPPFLAGS+=	-ggdb3
LDADD+=		${LIBDIR}/libuv.a -pthread
SRCS+=		main.cpp httpd.cpp

.include <bsd.prog.mk>
# vim: set ft=make ts=8 sw=8 noet:
