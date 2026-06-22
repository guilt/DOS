#!/bin/sh
#
# $Id: mkmft.sh,v 1.1 2002/04/20 08:48:08 richdawe Exp $
#
# mkmft.sh, Copyright (C) 2002 by Richard Dawe
#
# This script creates a .mft file of the files in the current directory.
# It takes the manifest name from a DSM file.
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

if [ "a$mft" = "a" ]; then
    echo "Could not determine manifest name from $DSM"
    exit 1
fi

# Generate manifest
echo "Generating manifest/$mft.mft..."
mkdir -p manifest || {
    echo "Could not create manifest directory"
    exit 1
}

# Do this twice, so the manifest is listed in the manifest.
find . ! -type d | sed -e 's:./::' | sort > manifest/$mft.mft
find . ! -type d | sed -e 's:./::' | sort > manifest/$mft.mft
