#! /bin/bash
#
# $Id: ac-host.sh,v 1.2 2001/04/18 00:11:22 richdawe Exp $
#
# ac-host.sh, Copyright (C) 1999, 2001 by Richard Dawe <richdawe@bigfoot.com>
#
# This script greps config.guess from the autoconf source for the
# <CPU>-<Company>-<Operating System> strings.

if [ "x$1" = 'x' ]; then
	echo 'Please specify the location of config.guess from autoconf source';
	exit 1;
fi

grep -E 'echo .+-.+-.+' $1 | sed 's/^.*echo //' | sed 's/#.*$//' | grep -v sed | grep -v ' exit '
