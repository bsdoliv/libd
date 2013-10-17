LIBQT_RELEASE=5.1

all: 
	@echo "try ${.MAKE} import"

SOURCES= src/corelib/codecs/qlatincodec.cpp \
	 src/corelib/codecs/qtextcodec.cpp \
	 src/corelib/tools/qstring.cpp \
	 src/corelib/tools/qscopedpointer.cpp \
	 src/corelib/tools/qchar.cpp \
	 src/corelib/global/qglobal.cpp \
	 src/corelib/thread/qatomic.cpp \
	 src/corelib/io/qdatastream.cpp \
	 src/corelib/io/qiodevice.cpp \
	 src/corelib/tools/qunicodetables.cpp

HEADERS= src/corelib/codecs/qlatincodec_p.h \
	 src/corelib/codecs/qtextcodec.h \
	 src/corelib/codecs/qtextcodec_p.h \
	 src/corelib/tools/qstring.h \
	 src/corelib/tools/qchar.h \
	 src/corelib/tools/qscopedpointer.h \
	 src/corelib/global/qglobal.h \
	 src/corelib/global/qsystemdetection.h \
	 src/corelib/global/qprocessordetection.h \
	 src/corelib/global/qcompilerdetection.h \
	 src/corelib/global/qglobalstatic.h \
	 src/corelib/thread/qatomic.h \
	 src/corelib/thread/qbasicatomic.h \
	 src/corelib/arch/qatomic_x86.h \
	 src/corelib/thread/qgenericatomic.h \
	 src/corelib/global/qlogging.h \
	 src/corelib/global/qflags.h \
	 src/corelib/global/qtypeinfo.h \
	 src/corelib/global/qtypetraits.h \
	 src/corelib/global/qsysinfo.h \
	 src/corelib/io/qdatastream.h \
	 src/corelib/io/qdatastream_p.h \
	 src/corelib/io/qiodevice.h \
	 src/corelib/io/qbuffer.h \
	 src/corelib/tools/qbytearray.h \
	 src/corelib/tools/qrefcount.h \
	 src/corelib/global/qnamespace.h \
	 src/corelib/global/qendian.h \
	 src/corelib/tools/qarraydata.h \
	 src/corelib/tools/qpair.h \
	 src/corelib/tools/qunicodetables_p.h \
	 src/corelib/kernel/qobjectdefs.h \
	 src/corelib/kernel/qobjectdefs_impl.h \
	 src/corelib/tools/qvector.h \
	 src/corelib/tools/qalgorithms.h \
	 src/corelib/tools/qiterator.h \
	 src/corelib/tools/qlist.h \
	 src/corelib/io/qdir.h \
	 src/corelib/io/qfileinfo.h \
	 src/corelib/io/qfile.h \
	 src/corelib/io/qfiledevice.h \
	 src/corelib/tools/qshareddata.h

.if !empty(QTBASEDIR)
import-sources: .PHONY
.for _m in ${SOURCES} ${HEADERS}
	sed 	-e "s:^#include <QtCore/:#include <:g" \
		-e "s:^#.*include <QtCore/:#include <:g" \
		-e "s:^#include \"QtCore/:#include \":g" \
		-e "s:^#include <qconfig.h>::g" \
		-e "s:^#include <qobject.h>::g" \
		-e "s:^#include \"qthreadstorage.h\"::g" \
		< ${QTBASEDIR}/${_m} > ${_m:T}
.endfor
	cat	${QTBASEDIR}/mkspecs/linux-g++-64/qplatformdefs.h | \
	sed	-e "s:^#include.*linux-g++/qplatformdefs.*::g" \
		-e "s:^#include.*common/posix/qplatformdefs.*::g" \
		-e "s:^#include.*c89/qplatformdefs.*::g" \
		> qplatformdefs.h
	cat 	${QTBASEDIR}/mkspecs/linux-g++/qplatformdefs.h | \
	sed	-e "s:^#include.*linux-g++/qplatformdefs.*::g" \
		-e "s:^#include.*common/posix/qplatformdefs.*::g" \
		-e "s:^#include.*c89/qplatformdefs.*::g" \
		>> qplatformdefs.h
	cat 	${QTBASEDIR}/mkspecs/common/posix/qplatformdefs.h | \
	sed	-e "s:^#include.*linux-g++/qplatformdefs.*::g" \
		-e "s:^#include.*common/posix/qplatformdefs.*::g" \
		-e "s:^#include.*c89/qplatformdefs.*::g" \
		>> qplatformdefs.h
	cat 	${QTBASEDIR}/mkspecs/common/c89/qplatformdefs.h | \
	sed	-e "s:^#include.*linux-g++/qplatformdefs.*::g" \
		-e "s:^#include.*common/posix/qplatformdefs.*::g" \
		-e "s:^#include.*c89/qplatformdefs.*::g" \
		>> qplatformdefs.h

.else
import-sources: .PHONY
	@echo "QTBASEDIR undefined"
.endif

qt.mk: ${SOURCES:T} ${HEADERS:T}
	-rm -f ${.TARGET}
	echo "CXXFLAGS+= -I${.CURDIR}" >> ${.TARGET}
	echo ".PATH: ${.CURDIR}" >> ${.TARGET}
	echo "SRCS+=${SOURCES:T}" >> ${.TARGET}
	echo "HDRS+=${HEADERS:T}" >> ${.TARGET}
	echo "HDRS+=qfeatures.h" >> ${.TARGET}
	echo "CXXFLAGS+= -DQT_NO_THREAD" >> ${.TARGET}
	echo "CXXFLAGS+= -DQT_NO_QOBJECT" >> ${.TARGET}
#        QT_BOOTSTRAPPED \
        QT_LITE_UNICODE \
        QT_NO_CAST_TO_ASCII \
        QT_NO_CODECS \
        QT_NO_DATASTREAM \
        QT_NO_LIBRARY \
        QT_NO_QOBJECT \
        QT_NO_SYSTEMLOCALE \
        QT_NO_THREAD \
        QT_NO_UNICODETABLES \
        QT_NO_USING_NAMESPACE \
        QT_NO_DEPRECATED \
        QT_NO_TRANSLATION \


qfeatures.h:
	echo > ${.TARGET}

import: .PHONY import-sources qt.mk qfeatures.h

# vim: set ts=8 sw=8 noet:
