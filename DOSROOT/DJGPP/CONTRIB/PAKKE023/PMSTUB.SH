#! /bin/bash
#
# $Id: pmstub.sh,v 1.4 2003/03/15 12:11:11 richdawe Exp $
#
# pmstub.sh, Copyright (C) 1999, 2001, 2003 by Richard Dawe
#
# Add a specified protected-mode stub to a specified file. For DJGPP programs
# this can be used to allow the program to run without requiring a DPMI server
# to be installed, by having the server built into the program.

if [ -n $1 -a $1 = "-x" ]; then
    shift
    set -x
fi

INPUT_EXE=$1
OUTPUT_EXE=$2
HOST_OS=$3
PMODE_STUB=$4

# No host OS => no idea what we should do.
if [ -z $HOST_OS ]; then
    echo "ABORTED: No host OS specified"
    exit 1
fi

# Can we find the P-mode stub? If not, abort.
if [ -n $PMODE_STUB ]; then
    if [ ! -x $PMODE_STUB ]; then
	echo "ABORTED: Protected mode stub '$PMODE_STUB' not found/executable"
	exit 1
    fi
fi

# Check that we have input and output filenames.
if [ -z $INPUT_EXE -o -z $OUTPUT_EXE ]; then
    echo "ABORTED: Filename(s) missing"
    exit 1
fi

# Check the input and output filenames are not the same.
if [ $INPUT_EXE = $OUTPUT_EXE ]; then
    echo "ABORTED: Input and output filenames identical"
    exit 1
fi

# Copy from input to output, if no stub specified.
if [ -z $PMODE_STUB ]; then
    echo "Copying $INPUT_EXE -> $OUTPUT_EXE"
    cp $INPUT_EXE $OUTPUT_EXE
    exit 0
fi

# Handle the operation appropriately
case $HOST_OS in
    msdosdjgpp)
	T_OUTPUT_EXE=`echo $OUTPUT_EXE | sed -e 's:/\([^/]*\):/t-\1:'`
	T_OUTPUT_EXE=`echo $T_OUTPUT_EXE | sed -e 's:^\([^/]*\):t-\1:'`
	T_OUTPUT_IMAGE=`echo $T_OUTPUT_EXE | sed -e 's:\.[eE][xX][eE]$::'`

	echo "Adding DPMI server stub to $INPUT_EXE -> $OUTPUT_EXE"
	cp $INPUT_EXE $T_OUTPUT_EXE
	exe2coff $T_OUTPUT_EXE
	cat $PMODE_STUB $T_OUTPUT_IMAGE > $OUTPUT_EXE
	rm -f $T_OUTPUT_EXE $T_OUTPUT_IMAGE
	;;

    *)
    ;;
esac
