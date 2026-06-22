#! /bin/sh
#
# pkgdsms.sh
# Copyright (C) 2001 by Richard Dawe
#
# Create a package of DSMs from the DJGPP archive. Usage:
#
# pkgdsms.sh <path to base of DJGPP archive>
#
# E.g. if you have a mirror of the DJGPP archive in /pub/djgpp/mirror,
# you would use:
#
#     pkgdsms.sh /pub/djgpp/mirror
#
# All files are created in the current directory.
#

# Constants
PROG=$(basename $0)
AUTHOR_NAME="Richard Dawe"
AUTHOR_EMAIL="rich@phekda.freeserve.co.uk"
AUTHOR="$AUTHOR_NAME <$AUTHOR_EMAIL>"
COPYRIGHT="Copyright (C) 2001 by $AUTHOR"

SUBDIRS="v2 v2apps v2gnu v2misc v2tk"
SHAREDIR=share/pakke/db-avail

DATETIME=$(date -I -u)
NAME=djgpp-dsms
FILENAME=ds$(date -u +%y%m%d)
PKGDSM=$FILENAME.dsm
PKGVER=$FILENAME.ver
PKGMFT=$FILENAME.mft
PKGZIP=$FILENAME.zip
VERSION=$(date -u +%Y).$(date -u +%m).$(date +%d)

# --- START ---

STARTDIR=$(pwd)
PACKAGE=$STARTDIR/$PKGZIP

# Parse arguments
BASEDIR=$1

if [ "a$BASEDIR" = "a" ]; then
    echo "No base directory specified!"
    exit 1
fi

# Create a log file
LOGFILE=$STARTDIR/pkgdsms-$$.log
echo "Logging to $LOGFILE"

# Create and change into the build directory
BUILDDIR=$STARTDIR/pkgdsms.$$

if [ -d $BUILDDIR ]; then
    echo "$BUILDDIR already exists!"
    exit 1
fi

echo "Using build directory $BUILDDIR" >> $LOGFILE

# Extract DSMs into the share directory
mkdir -p $BUILDDIR/$SHAREDIR
cd $BUILDDIR/$SHAREDIR

for subdir in $SUBDIRS; do
    echo -n "Processing $subdir..."

    for zip in $(find $BASEDIR/$subdir -name '*.zip'); do
	unzip -q -n -j $zip 'manifest/*.dsm' 1>>$LOGFILE 2>&1
    done

    echo "done"
done

# Count total number of packages
PACKAGECOUNT=$(for subdir in $SUBDIRS; do find $BASEDIR/$subdir -name '*.zip'; done | wc -l | sed -e 's:^[ \t]+::')

# Create DSM, version and manifest files
mkdir -p $BUILDDIR/manifest
cd $BUILDDIR

DSM=$BUILDDIR/manifest/$PKGDSM
VER=$BUILDDIR/manifest/$PKGVER
MFT=$BUILDDIR/manifest/$PKGMFT

# DSM to place into the package
cat <<EOF > $DSM
#
# Package of DSMs for packages in the DJGPP archive.
# Created automatically on $DATETIME by $PROG
# $PROG, $COPYRIGHT
#

dsm-file-version: 1.0
dsm-author: $AUTHOR
dsm-name: $FILENAME
dsm-version: 0.5.0
dsm-type: binaries

name: $NAME
version: $VERSION
manifest: $FILENAME
short-description: DJGPP Software Manifests for DJGPP packages $DATETIME

author: $AUTHOR_NAME
author-email: $AUTHOR_EMAIL

simtelnet-path: v2/
zip: $PKGZIP

replaces: $NAME < $VERSION
EOF

# .ver file to place into the package
cat <<EOF > $VER
$FILENAME DJGPP Software Manifests for DJGPP packages $DATETIME (binaries)
EOF

# Count DSMs
DSMCOUNT=$(find . ! -type d | wc -l | sed -e 's:^[ \t]+::')

# Construct manifest
find . ! -type d | sed -e 's:./::' | sort > $MFT
find . ! -type d | sed -e 's:./::' | sort > $MFT

# Build the package
cat $MFT | xargs zip -9 $PACKAGE >>$LOGFILE

# Remove temporary files
echo -n "Removing temporary directory $BUILDDIR..."
rm -Rf $BUILDDIR
echo "done"

msg="$PACKAGE contains $DSMCOUNT DSMs (from $PACKAGECOUNT packages)"
echo $msg
echo $msg >>$LOGFILE

echo "Done!"
