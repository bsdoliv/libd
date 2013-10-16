.ifndef LIBD_MK
LIBD_MK=

LDADD+=	-L${LIBDIR}
LDADD+=	-luv
LDADD+=	-ldcore

.endif # !LIBD_MK

# vim: set ts=8 sw=8 noet:
