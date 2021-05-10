#! /bin/bash
#
# $Id: gdbx.sh,v 1.2 2001/04/18 00:11:22 richdawe Exp $
#
# gdbx.sh - Run gdb with all source directories
#

DIRS=`find ./src -type d -print`
GDBPARAMS=''

for i in $DIRS; do GDBPARAMS="$GDBPARAMS --dir=$i"; done
gdb $GDBPARAMS $*
