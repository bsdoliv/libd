.ifndef CPP_MK
CPP_MK=

MKPICINSTALL=   no # disables install of lib*_pic.a
MKPICLIB=   	no # disables build of lib*_pic.a
MKMAN=      	no # disables manpages build

CXXFLAGS+= -Wextra -W

.endif # !CPP_MK
