.ifndef VARS_MK
VARS_MK=

DEST_DIR=	${ABSTOP}/obj
BINDIR=		${DEST_DIR}/bin
LIBDIR=		${DEST_DIR}/lib
INCLUDEDIR=	${DEST_DIR}/include
HOST_OS!=	uname -s

.if (${HOST_OS} == "OpenBSD")
GMAKE=		/usr/local/bin/gmake
.else
GMAKE=		/usr/bin/make
.endif

.endif
# vim: set ft=make ts=8 sw=8 noet:
