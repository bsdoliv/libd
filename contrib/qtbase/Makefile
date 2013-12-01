.include <bsd.own.mk>

.include "../Makefile.inc"
.include "${ABSTOP}/mk/cpp.mk"

CXXFLAGS+=	-std=c++0x
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
