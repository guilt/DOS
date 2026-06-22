# Sed script for DJGPP specific editing of Makefile.

# Include _libsupp.h
/^DEFAULT_INCLUDES[	 ]*=/ s|$| -I$(top_srcdir)/djgpp|
