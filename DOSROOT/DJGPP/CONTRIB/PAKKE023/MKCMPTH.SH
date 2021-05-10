#! /bin/bash
#
# $Id: mkcmpth.sh,v 1.6 2002/06/23 20:28:30 richdawe Exp $
#
# mkcmpth.sh, Copyright (C) 2000 by Laurynas Biveinis
#
# This is based on part of the original pakke Makefile. Some modifications
# were made by Richard Dawe and Tim van Holder.
#
# This script constructs comptime.c in the current directory.
# This contains information about how pakke was built. The build info can be
# displayed by running pakke like this: 'pakke -V'.

exec 5>comptime.c
cat >&5 <<EOF
/* Generated automagically by $0 -- do not edit */

#include "comptime.h"

const char* pakke_build_date = __DATE__;
const char* pakke_build_time = __TIME__;
EOF


if test -z "$HOSTNAME"; then
  # This needs a bit of sed'ing. The hostname returned by hostname from
  # shellutils 1.12 has spurious spaces in it, because of a bug in earlier
  # versions of DJGPP's libc.
  HOSTNAME=`hostname | sed -e 's:^[ \t]*\([^ \t]*\)[ \t]*$:\1:'`
fi
echo "const char* pakke_build_host = \"$HOSTNAME\";" >&5


if test -z "$USER"; then
  USER=`logname`
fi
echo "const char* pakke_build_user = \"$USER\";" >&5


USERMAIL=$1
echo "const char* pakke_build_user_mail = \"$USERMAIL\";" >&5


GCC=`gcc -v 2>&1 | grep version`
echo "const char* pakke_build_gcc = \"$GCC\";" >&5


# Parse the binutils version from as's version output.
BINUTILS_VERSION=`as --version | head -q -n 1 - | sed -e 's:^[a-zA-Z ]*::'`
echo "const char* pakke_build_binutils = \"binutils $BINUTILS_VERSION\";" >&5


UNAME=`uname -m -r -s`
echo "const char* pakke_build_uname = \"$UNAME\";" >&5


DEFAULT_PLATFORM=$2
echo "const char* pakke_build_platform_default = \"$DEFAULT_PLATFORM\";" >&5
