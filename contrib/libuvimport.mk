LIBUV_RELEASE=0.11.1

all: 
	@echo "try ${.MAKE} patch"

PATCH_BUILD+= build.mk
PATCH_BUILD+= config-mingw.mk
PATCH_BUILD+= config-unix.mk

CLEAN_FILES+= gyp_uv
CLEAN_FILES+= uv.gyp
CLEAN_FILES+= vcbuild.bat
CLEAN_FILES+= common.gypi

CHANGESET+=${CHANGES}

mk:
	mkdir -p ${.TARGET}

.for _mk in ${PATCH_BUILD}
patch-build: .PHONY mk/${_mk}
mk/${_mk}: mk ${_mk}
	sed "s:^include \$$(SRCDIR)/:include \$$(SRCDIR)/mk/:g" < ${.ALLSRC} > ${.TARGET}
.endfor

clean-files: .PHONY
	rm -fv ${CLEAN_FILES}

patch-makefile: .PHONY GNUmakefile

GNUmakefile: Makefile
	sed "s:^include \$$(SRCDIR)/build.mk:include \$$(SRCDIR)/mk/build.mk:g" < ${.ALLSRC} > .${.TARGET}

patch: patch-build clean-files patch-makefile

# vim: set ts=8 sw=8 noet:
