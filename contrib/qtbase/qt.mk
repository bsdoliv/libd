.PATH: /home/aoliveira/libd/contrib/qtbase
SRCS= qstring.cpp qchar.cpp qdebug.cpp qarraydata.cpp qtextcodec.cpp qglobal.cpp qregexp.cpp qregularexpression.cpp qbytearray.cpp
FILES= qstring.h qchar.h qdebug.h qbytearray.h qregularexpression.h qlatincodec_p.h qtextcodec.h qtextcodec_p.h qscopedpointer.h qglobal.h qsystemdetection.h qprocessordetection.h qcompilerdetection.h qglobalstatic.h qatomic.h qbasicatomic.h qthreadstorage.h qatomic_x86.h qgenericatomic.h qlogging.h qflags.h qtypeinfo.h qtypetraits.h qsysinfo.h qdatastream.h qdatastream_p.h qiodevice.h qbuffer.h qbytearraymatcher.h qbitarray.h qrefcount.h qnamespace.h qendian.h qarraydata.h qpair.h qunicodetables_p.h qobjectdefs.h qobjectdefs_impl.h qvector.h qalgorithms.h qiterator.h qlist.h qdir.h qfileinfo.h qfile.h qfiledevice.h qshareddata.h qmetatype.h qvarlengtharray.h qcontainerfwd.h qisenum.h qstringlist.h qregexp.h qstringmatcher.h qdatetime.h qsharedpointer.h qsharedpointer_impl.h qhash.h qcache.h qmap.h qset.h qcontiguouscache.h qtextstream.h qtextstream_p.h qiodevice_p.h qlocale.h qlocale_p.h qringbuffer_p.h qregularexpression.h qsimd_p.h qutfcodec_p.h qnumeric.h qnumeric_p.h qcoreapplication_p.h qcoreapplication.h qtranslator.h qtools_p.h qcollator_p.h qfunctions_p.h qsettings.h qcoreglobaldata_p.h qreadwritelock.h qmutex.h qtsciicodec_p.h qisciicodec_p.h qiconvcodec_p.h qsimplecodec_p.h qgb18030codec_p.h qeucjpcodec_p.h qjpunicode_p.h qjiscodec_p.h qsjiscodec_p.h qeuckrcodec_p.h qbig5codec_p.h qvariant.h
FILES+= qt.h
FILES+= Qt
FILES+= qfeatures.h
CXXFLAGS+= -I.
CXXFLAGS+= -DQT_NO_QOBJECT
CXXFLAGS+= -DQT_NO_CODECS
CXXFLAGS+= -DQT_NO_UNICODETABLES
CXXFLAGS+= -DQT_NO_DATASTREAM
CXXFLAGS+= -DQT_NO_TRANSLATION
