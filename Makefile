.include "Makefile.inc"

distrib: .PHONY
	mkdir -p ${BINDIR} ${LIBDIR}

distclean: .PHONY
	rm -rfv ./obj

# vim: set ft=make ts=8 sw=8 noet:
