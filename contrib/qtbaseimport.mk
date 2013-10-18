LIBQT_RELEASE=5.1

# TODO - improvements
#	. seperate HEADERS/SOURCES per original-module/folder
#	. patch model enabling us to easily generate and apply patches on the
#	fly

all: 
	@echo "try ${.MAKE} import"

SOURCES_EXCEPTION= qchar.cpp \
		   qstringmatcher.cpp

SOURCES= src/corelib/codecs/qlatincodec.cpp \
	 src/corelib/codecs/qtextcodec.cpp \
	 src/corelib/tools/qstring.cpp \
	 src/corelib/tools/qscopedpointer.cpp \
	 src/corelib/tools/qchar.cpp \
	 src/corelib/tools/qstringmatcher.cpp \
	 src/corelib/global/qglobal.cpp \
	 src/corelib/thread/qatomic.cpp \
	 src/corelib/io/qdatastream.cpp \
	 src/corelib/io/qiodevice.cpp \
	 src/corelib/tools/qunicodetables.cpp \
	 src/corelib/io/qdebug.cpp \
	 src/corelib/tools/qbytearray.cpp

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
	 src/corelib/tools/qbytearraymatcher.h \
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
	 src/corelib/tools/qshareddata.h \
	 src/corelib/kernel/qmetatype.h \
	 src/corelib/tools/qvarlengtharray.h \
	 src/corelib/tools/qcontainerfwd.h \
	 src/corelib/global/qisenum.h \
	 src/corelib/tools/qstringlist.h \
	 src/corelib/tools/qregexp.h \
	 src/corelib/tools/qstringmatcher.h \
	 src/corelib/tools/qdatetime.h \
	 src/corelib/tools/qsharedpointer.h \
	 src/corelib/tools/qsharedpointer_impl.h \
	 src/corelib/tools/qhash.h \
	 src/corelib/tools/qmap.h \
	 src/corelib/tools/qset.h \
	 src/corelib/tools/qcontiguouscache.h \
	 src/corelib/io/qdebug.h \
	 src/corelib/io/qtextstream.h \
	 src/corelib/io/qtextstream_p.h \
	 src/corelib/io/qiodevice_p.h \
	 src/corelib/tools/qlocale.h \
	 src/corelib/tools/qlocale_p.h \
	 src/corelib/tools/qringbuffer_p.h \
	 src/corelib/tools/qregularexpression.h \
	 src/corelib/tools/qsimd_p.h \
	 src/corelib/codecs/qutfcodec_p.h \
	 src/corelib/global/qnumeric.h \
	 src/corelib/global/qnumeric_p.h \
	 src/corelib/kernel/qcoreapplication_p.h \
	 src/corelib/kernel/qcoreapplication.h \
	 src/corelib/kernel/qtranslator.h \
	 src/corelib/tools/qtools_p.h \
	 src/corelib/tools/qcollator_p.h \
	 src/corelib/kernel/qfunctions_p.h \
	 src/corelib/io/qsettings.h \
	 src/corelib/kernel/qcoreglobaldata_p.h \
	 src/corelib/thread/qreadwritelock.h \
	 src/corelib/thread/qmutex.h \
	 src/corelib/codecs/qtsciicodec_p.h \
	 src/corelib/codecs/qisciicodec_p.h \
	 src/corelib/codecs/qiconvcodec_p.h \
	 src/corelib/codecs/qsimplecodec_p.h \
	 src/corelib/codecs/qgb18030codec_p.h \
	 src/corelib/codecs/qeucjpcodec_p.h \
	 src/corelib/codecs/qjpunicode_p.h \
	 src/corelib/codecs/qjiscodec_p.h \
	 src/corelib/codecs/qsjiscodec_p.h \
	 src/corelib/codecs/qeuckrcodec_p.h \
	 src/corelib/codecs/qbig5codec_p.h \
	 src/corelib/kernel/qvariant.h

.if !empty(QTBASEDIR)
import-sources: .PHONY
.for _m in ${SOURCES} ${HEADERS}
	sed 	-e "s:^#include <QtCore/:#include <:g" \
		-e "s:^#.*include <QtCore/:#include <:g" \
		-e "s:^#include \"QtCore/:#include \":g" \
		-e "s:^#include <qconfig.h>::g" \
		-e "s:^#include <qobject.h>::g" \
		-e "s:^#include \"qthreadstorage.h\"::g" \
		-e "s:^#include \"private/:#include \":g" \
		-e "s:^#include <private/:#include <:g" \
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

# patch undesirable files
_SRCS=${SOURCES:T}
.for _e in ${SOURCES_EXCEPTION}
_SRCS:=${_SRCS:S/${_e}//}
.endfor

qt.mk: ${SOURCES:T} ${HEADERS:T}
	-rm -f ${.TARGET}
	echo "CXXFLAGS+= -I${.CURDIR}" >> ${.TARGET}
	echo ".PATH: ${.CURDIR}" >> ${.TARGET}
	echo "SRCS+=${_SRCS}" >> ${.TARGET}
	echo "HDRS+=${HEADERS:T}" >> ${.TARGET}
	echo "HDRS+=qfeatures.h" >> ${.TARGET}
	echo "CXXFLAGS+= -DQT_NO_THREAD" >> ${.TARGET}
	echo "CXXFLAGS+= -DQT_NO_QOBJECT" >> ${.TARGET}
	echo "CXXFLAGS+= -DQT_NO_CODECS" >> ${.TARGET}
	echo "CXXFLAGS+= -DQT_NO_UNICODETABLES" >> ${.TARGET}
	echo "CXXFLAGS+= -DQT_NO_DATASTREAM" >> ${.TARGET}
	echo "CXXFLAGS+= -DQT_NO_TRANSLATION" >> ${.TARGET}
	echo "qt.h: ${HEADERS:T}" >> ${.TARGET}
#.for _e in ${SOURCES_EXCEPTION}
#	echo "\t echo '#include 
#_SRCS:=${_SRCS:S/${_e}//}
#	${HEADERS:T}" >> ${.TARGET}
#.endfor
	
qfeatures.h:
	echo > ${.TARGET}

import: .PHONY import-sources qt.mk qfeatures.h

# vim: set ts=8 sw=8 noet:
