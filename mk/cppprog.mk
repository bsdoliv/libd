.ifndef CPPPROG_MK
CPPPROG_MK=

NOGCCERROR= 	1 # removes -Werror

CC=${CXX}

CXXFLAGS+= -pipe -fPIC -Wall 
CXXFLAGS+= -pthread 
#CPPFLAGS+= -I${ABSTOP}
#CXXFLAGS+= -std=c++0x 
#CXXFLAGS+= -g -DDEBUG
#CXXFLAGS+= -O3
#CPPFLAGS+= -I/usr/include/thrift -I/usr/include/thrift/fb303
# -lthrift -lfb303 -lmemcached -lssl -lrt -lcrypto -lwajam-nlp

LDADD+= -lpthread 

.SUFFIXES: .d
.cpp.d:
	${CXX} -M ${CXXFLAGS} ${CPPFLAGS} ${.IMPSRC} | \
	sed 's!\.o[ :]*!.o : ${.TARGET} !' > ${.TARGET}

DFILES= ${SRCS:T:S/.cpp/.d/}
CLEANFILES+= ${DFILES} .depend_local

.depend_local: ${DFILES}
.if empty(${DFILES})
	echo > ${.TARGET}
.else
	cat ${.ALLSRC} > ${.TARGET}
.endif

.-include ".depend_local"

.if !exists(.depend_local)
.ifnmake distclean && cleandir && clean
.BEGIN: .depend_local
	@${.MAKE}
.endif
.endif

.if exists(.depend_local)
.ifnmake distclean && cleandir && clean
.END: .depend_local
.endif
.endif

.endif # !CPPPROG_MK
# vim: set ft=make ts=8 sw=8 noet:
