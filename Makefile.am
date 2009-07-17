## Process this file with automake to produce Makefile.in
## Created by Anjuta

SUBDIRS = src 

canndocdir = ${prefix}/doc/cann
canndoc_DATA = \
	README\
	COPYING\
	AUTHORS\
	ChangeLog\
	INSTALL\
	NEWS


EXTRA_DIST = $(canndoc_DATA)


# Remove doc directory on uninstall
uninstall-local:
	-rm -r $(canndocdir)
