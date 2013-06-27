AUTOMAKE_OPTIONS = foreign no-installinfo no-installman

ACLOCAL_AMFLAGS  = -I../m4
lib_LIBRARIES    = libspencer_regexp.a
libspencer_regexp_a_SOURCES = regexp.c regerror.c regsub.c regexp.h regmagic.h
include_HEADERS  = spencer_regexp.h
man_MANS         = regexp.3
EXTRA_DIST       = Imakefile $(man_MANS)
