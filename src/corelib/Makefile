.include <bsd.own.mk>

.include "../Makefile.inc"
.include "${ABSTOP}/mk/cpp.mk"
.include "${ABSTOP}/mk/include.mk"
.include "${ABSTOP}/contrib/qtbase/qt.mk"

CXXFLAGS+=	-std=c++0x
CXXFLAGS+=	-I${ABSTOP}/contrib/libuv/include
#CXXFLAGS+=	-ggdb3
LDSTATIC= 	-static
LIB=		dcore

SRCS+= daemon.cpp httpdaemon.cpp uvwrapper.cpp

FILES= dglobal.h
FILES+= Daemon daemon.h
FILES+= HttpDaemon httpdaemon.h
#FILES+= Qt
FILESMODE= 600

Qt: qt.h
	echo '#include "qt.h"' > ${.TARGET}

.include <bsd.lib.mk>

# vim: set ft=make ts=8 sw=8 noet:
