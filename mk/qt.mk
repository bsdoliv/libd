.ifndef QT_MK
QT_MK=

.include "${.PARSEDIR}/vars.mk"

CXXFLAGS+= -I${INCLUDEDIR}/qt
LDADD+=		-lqt
LDADD+=		-lz

.endif # !QT_MK
