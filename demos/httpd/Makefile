.include "../Makefile.inc"
.include "${ABSTOP}/mk/cppprog.mk"
.include "${ABSTOP}/mk/libd.mk"

PROG=		httpd
CPPFLAGS+=	-I${INCLUDEDIR}
SRCS+=		main.cpp httpd.cpp

.include <bsd.prog.mk>
# vim: set ft=make ts=8 sw=8 noet:
