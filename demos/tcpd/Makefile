.include "../Makefile.inc"
.include "${ABSTOP}/mk/cppprog.mk"
.include "${ABSTOP}/mk/libd.mk"

PROG=		tcpd
CPPFLAGS+=	-I${INCLUDEDIR}
CPPFLAGS+=	-ggdb3
SRCS+=		main.cpp tcpd.cpp

.include <bsd.prog.mk>
# vim: set ft=make ts=8 sw=8 noet:
