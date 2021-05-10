#!/bin/sh
#
# $Id: dsm2ver.sh,v 1.2 2003/02/20 21:50:41 richdawe Exp $
#
# dsm2ver.sh, Copyright (C) 2002, 2003 by Richard Dawe
#
# This script creates a .ver file from a DSM file.
#

# Parse args
if [ "a$1" = "a-g" ]; then
    set -x
    shift
fi

DSM=$1

if [ "a$DSM" = "a" ]; then
    echo "Syntax: $0 <DSM file>"
    exit 1
fi

# Get DSM components
mft=\
$(egrep '^ *manifest:' $DSM \
    | sed -e 's,^ *manifest:,,' -e 's,^ *,,' -e 's, *$,,')

package=\
$(egrep '^ *name:' $DSM \
    | sed -e 's,^ *name:,,' -e 's,^ *,,' -e 's, *$,,')

description=\
$(egrep '^ *short-description:' $DSM \
    | sed -e 's,^ *short-description:,,' -e 's,^ *,,' -e 's, *$,,')

version=\
$(egrep '^ *version:' $DSM \
    | sed -e 's,^ *version:,,' -e 's,^ *,,' -e 's, *$,,')

type=\
$(egrep '^ *type:' $DSM \
    | sed -e 's,^ *type:,,' -e 's,^ *,,' -e 's, *$,,')

ver="$mft $package"
if [ "a$description" != "a" ]; then
    ver="$ver, $description,"
fi
ver="$ver $version ($type)"

echo $ver
