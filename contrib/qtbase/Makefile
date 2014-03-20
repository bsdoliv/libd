.include <bsd.own.mk>

.include "../Makefile.inc"
.include "${ABSTOP}/mk/cpp.mk"

.if (${HOST_OS} != "OpenBSD")
CXXFLAGS+=	-std=c++0x
.endif
LDSTATIC=	-static
LIB=		qt

build: .PHONY all

.include "qt.mk"

FILES+= Qt
=======
FILES+=		Qt
FILES+=		qplatformdefs.h
FILESDIR=	${INCLUDEDIR}/qt

.include <bsd.lib.mk>

# vim: set ts=8 sw=8 noet:
