#! /bin/bash
#
# $Id: dsmgen.sh,v 1.8 2003/02/21 18:15:42 richdawe Exp $
#
# dsmgen.sh, Copyright (C) 1999-2003 by Richard Dawe
#
# Automatic DSM generator

# Read in default settings, if any.
if [ -f $HOME/dsmgenrc ]; then
    . $HOME/dsmgenrc
fi

# Get package details
PACKAGE=$1
PACKAGE_VERSION=$2
PACKAGE_TYPE=$3
MANIFEST=$4
ZIP=$5
SIMTELNET_PATH=$6

# Syntax / help message
if [    "a$PACKAGE" = "a"      \
     -o "$PACKAGE" = "-h"      \
     -o "$PACKAGE" = "--help"  \
     -o "a$PACKAGE_TYPE" = "a" \
     -o "a$MANIFEST" = "a" ]; then
    cat <<EOF

Syntax: $0
        <Package> <Package version> <Package type = (b|s|d|g|v)>
        <Manifest> [<Zip file> [<Simtelnet path>]]

Set the default author & author's e-mail address using the AUTHOR
and AUTHOR_EMAIL environment variables. To set these permanently,
create a shell script called \$HOME/dsmgenrc like so:

    AUTHOR="Fred Bloggs"
    AUTHOR_EMAIL="fred@bloggs.com"

$0 will source this script automatically.

EOF
    exit 0
fi 

# Defaults
if [ "a$ZIP" = "a" ]; then
    ZIP="$MANIFEST.zip"
fi

# Parse the package type
i=$PACKAGE_TYPE

case $i in
# Binaries
b*)    
    PACKAGE_TYPE=binaries
    ;;

# Sources
s*)
    PACKAGE_TYPE=sources
    ;;

# Documentation
d*)
    PACKAGE_TYPE=documentation
    ;;

# Group
g*)
    PACKAGE_TYPE=group
    ;;

# Virtual
v*)
    PACKAGE_TYPE=virtual
    ;;

    # Error on default
*)
    exit 1
    ;;
esac

# Get today's date
TODAYS_DATE=$(date +%Y-%m-%d)

# Generate the DSM
cat <<EOF
#
# DSM for $PACKAGE $PACKAGE_VERSION $PACKAGE_TYPE
# Written by $AUTHOR <$AUTHOR_EMAIL> $TODAYS_DATE
#

dsm-file-version: 1.0
dsm-name: $MANIFEST
dsm-version: 0.6.1

dsm-author: $AUTHOR
dsm-author-email: $AUTHOR_EMAIL

name: $PACKAGE
version: $PACKAGE_VERSION
type: $PACKAGE_TYPE
manifest: $MANIFEST

short-description:
license:

simtelnet-path: $SIMTELNET_PATH
zip: $ZIP
EOF

if [ "$PACKAGE_TYPE" = "binaries" ]; then
    cat <<EOF

replaces: $PACKAGE < $PACKAGE_VERSION
EOF
fi
