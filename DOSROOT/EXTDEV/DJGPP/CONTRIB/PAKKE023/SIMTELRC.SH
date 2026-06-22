#! /bin/bash
#
# $Id: simtelrc.sh,v 1.4 2002/04/28 15:55:39 richdawe Exp $
# Copyright (C) 1999-2002 by Richard Dawe
#

# Download the list of mirrors from here:
URL='ftp://ftp.mirror.ac.uk/sites/ftp.simtel.net/pub/simtelnet/MIRRORS.TXT'
# Or, better still, from the central site
# URL='ftp://ftp.simtel.net/pub/simtelnet/MIRRORS.TXT'

wget -q -O - $URL \
    | egrep 'ftp://|http://' \
    | perl -n -e 's/^[^:]*ftp/ftp/; s/^[^:].*http/http/; s/\s+.*$//; print $_."\n";' \
    | sort | uniq
