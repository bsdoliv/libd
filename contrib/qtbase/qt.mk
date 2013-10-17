CXXFLAGS+= -I/home/aoliveira/libd/contrib/qtbase
.PATH: /home/aoliveira/libd/contrib/qtbase
SRCS+=qlatincodec.cpp qtextcodec.cpp qstring.cpp qscopedpointer.cpp qchar.cpp qglobal.cpp qatomic.cpp qdatastream.cpp qiodevice.cpp qunicodetables.cpp
HDRS+=qlatincodec_p.h qtextcodec.h qtextcodec_p.h qstring.h qchar.h qscopedpointer.h qglobal.h qsystemdetection.h qprocessordetection.h qcompilerdetection.h qglobalstatic.h qatomic.h qbasicatomic.h qatomic_x86.h qgenericatomic.h qlogging.h qflags.h qtypeinfo.h qtypetraits.h qsysinfo.h qdatastream.h qdatastream_p.h qiodevice.h qbuffer.h qbytearray.h qrefcount.h qnamespace.h qendian.h qarraydata.h qpair.h qunicodetables_p.h qobjectdefs.h qobjectdefs_impl.h qvector.h qalgorithms.h qiterator.h qlist.h qdir.h qfileinfo.h qfile.h qfiledevice.h qshareddata.h
HDRS+=qfeatures.h
CXXFLAGS+= -DQT_NO_THREAD
CXXFLAGS+= -DQT_NO_QOBJECT
