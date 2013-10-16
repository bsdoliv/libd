.include <bsd.own.mk>
.include <bsd.sys.mk>

.include "../Makefile.inc"
.include "${ABSTOP}/mk/cpp.mk"
.include "${ABSTOP}/mk/include.mk"

CXXFLAGS+=	-std=c++0x
CXXFLAGS+=	-I${INCLUDEDIR}
LDSTATIC= 	-static
LIB=		dcore

SRCS+= daemon.cpp httpdaemon.cpp

FILES= dglobal.h
FILES+= Daemon daemon.h
FILES+= HttpDaemon httpdaemon.h
FILESMODE= 600

.include <bsd.lib.mk>

# vim: set ft=make ts=8 sw=8 noet:
