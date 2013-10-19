.ifndef QT_MK
QT_MK=

.include "${.PARSEDIR}/vars.mk"

CXXFLAGS+= -DQT_NO_THREAD
CXXFLAGS+= -DQT_NO_QOBJECT
CXXFLAGS+= -DQT_NO_CODECS
CXXFLAGS+= -DQT_NO_UNICODETABLES
CXXFLAGS+= -DQT_NO_DATASTREAM
CXXFLAGS+= -DQT_NO_TRANSLATION
CXXFLAGS+= -I${INCLUDEDIR}/qt
LDADD+=		-lqt
LDADD+=		-lz

.endif # !QT_MK
