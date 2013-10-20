.ifndef LIBD_MK
LIBD_MK=

LDADD+=	-L${LIBDIR}
LDADD+=	-ldcore
LDADD+=	${LIBDIR}/libuv.a

# qt link flags should necessarily come after
.include "${ABSTOP}/mk/qt.mk"

.endif # !LIBD_MK

# vim: set ts=8 sw=8 noet:
