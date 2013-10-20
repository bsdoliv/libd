.PATH: /home/andre/libd/contrib/qtbase
SRCS= qstring.cpp qstringlist.cpp qbytearraymatcher.cpp qsystemerror.cpp qstack.cpp qlatincodec.cpp qtextstream.cpp qfilesystemengine.cpp qfilesystemengine_unix.cpp qchar.cpp qdebug.cpp qdiriterator.cpp qfilesystemiterator_unix.cpp qdir.cpp qtemporaryfile.cpp qarraydata.cpp qtextcodec.cpp qutfcodec.cpp qglobal.cpp qregexp.cpp qlogging.cpp qdatastream.cpp qlist.cpp qlocale.cpp qlocale_tools.cpp qnumeric.cpp qmap.cpp qiodevice.cpp qfiledevice.cpp qfilesystementry.cpp qfile.cpp qfsfileengine.cpp qfsfileengine_unix.cpp qabstractfileengine.cpp qfileinfo.cpp qmalloc.cpp qfsfileengine_iterator.cpp qcoreglobaldata.cpp qbuffer.cpp qipaddress.cpp qhash.cpp qbitarray.cpp qdatetime.cpp qbytearray.cpp
FILES= qstring.h qchar.h qdebug.h qbytearray.h qregularexpression.h qfilesystemiterator_p.h qsystemlibrary_p.h qstringbuilder.h qfilesystementry_p.h qtemporaryfile.h qipaddress_p.h qtemporaryfile_p.h qlatincodec_p.h qtextcodec.h qtextcodec_p.h qscopedpointer.h qstack.h qglobal.h qsystemdetection.h qprocessordetection.h qcompilerdetection.h qglobalstatic.h qatomic.h qthread.h qbasicatomic.h qthreadstorage.h qatomic_x86.h qatomic_bootstrap.h qgenericatomic.h qlogging.h qflags.h qtypeinfo.h qtypetraits.h qsysinfo.h qdatastream.h qdatastream_p.h qiodevice.h qbuffer.h qbytearraymatcher.h qbitarray.h qrefcount.h qnamespace.h qendian.h qarraydata.h qpair.h qunicodetables_p.h qobjectdefs.h qmetaobject.h qobjectdefs_impl.h qvector.h qalgorithms.h qiterator.h qlist.h qdir.h qdir_p.h qdiriterator.h qfileinfo.h qfileinfo_p.h qfile.h qfsfileengine_p.h qfsfileengine_iterator_p.h qfilesystemengine_p.h qabstractfileengine_p.h qfiledevice_p.h qfilesystemmetadata_p.h qfile_p.h qtemporaryfile.h qfilesystementry_p.h qfiledevice.h qshareddata.h qmetatype.h qsystemerror_p.h qcore_unix_p.h qvarlengtharray.h qcontainerfwd.h qisenum.h qstringlist.h qregexp.h qstringmatcher.h qdatetime.h qdatetime_p.h qsharedpointer.h qsharedpointer_impl.h qhash.h qcache.h qmap.h qset.h qcontiguouscache.h qtextstream.h qtextstream_p.h qiodevice_p.h qlocale.h qlocale_tools_p.h qlocale_data_p.h qlocale_p.h qringbuffer_p.h qregularexpression.h qsimd_p.h qutfcodec_p.h qnumeric.h qnumeric_p.h qcoreapplication_p.h qcoreapplication.h qtranslator.h qtools_p.h qcollator_p.h qfunctions_p.h qsettings.h qcoreglobaldata_p.h qreadwritelock.h qmutex.h qtsciicodec_p.h qisciicodec_p.h qiconvcodec_p.h qsimplecodec_p.h qgb18030codec_p.h qeucjpcodec_p.h qjpunicode_p.h qjiscodec_p.h qsjiscodec_p.h qeuckrcodec_p.h qbig5codec_p.h qvariant.h
FILES+= qt.h
FILES+= Qt
FILES+= qfeatures.h
CXXFLAGS+= -I.
CXXFLAGS+= -DQT_NO_THREAD
CXXFLAGS+= -DQT_NO_QOBJECT
CXXFLAGS+= -DQT_NO_CODECS
CXXFLAGS+= -DQT_NO_UNICODETABLES
CXXFLAGS+= -DQT_NO_DATASTREAM
CXXFLAGS+= -DQT_NO_TRANSLATION
CXXFLAGS+= -DQT_BOOTSTRAPPED
CXXFLAGS+= -DQT_LITE_UNICODE
CXXFLAGS+= -DQT_NO_CAST_TO_ASCII
CXXFLAGS+= -DQT_NO_LIBRARY
CXXFLAGS+= -DQT_NO_SYSTEMLOCALE
CXXFLAGS+= -DQT_NO_TRANSLATION
CXXFLAGS+= -DQT_QMAKE_LOCATION
CXXFLAGS+= -DQT_NO_CAST_FROM_ASCII
