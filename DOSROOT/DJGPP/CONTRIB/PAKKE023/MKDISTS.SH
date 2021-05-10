#! /bin/bash
# $Id: mkdists.sh,v 1.1 2003/03/14 22:59:58 richdawe Exp $
# Copyright (C) 2003 by Richard Dawe
#
# Build distributions of pakke.

copy_into_manifest () {
    mkdir -p manifest
    for i in dsm ver; do
	cp -pv $1.$i manifest
    done
}

kill_cvs () {
    find . -type d -iname CVS | xargs rm -vrf
    find . -name .cvsignore   | xargs rm -vf
}

make_manifest () {
    # Do this twice, so the manifest includes itself in the listing.
    for i in 1 2; do
	find . ! -type d | sed -e 's:./::' | sort > $1
    done
}

make_zip () {
    rm -vf $1
    zip -r -9 $1 *
}

# Filename case is important.
export FNCASE=y

if (! test -f README); then
    echo "$0 must be run from the top-level directory!"
    exit 1
fi

# Ensure everything is built, including docs.
make all dvi ps || exit 1

# Build up what automake thinks should be a source tarball.
make dist-zip || exit 1

# Build the distribution directories.
ver=`grep '^AC_INIT' configure.ac \
| sed -e 's:^[^,]*,\([^,]*\),.*$:\1:' -e 's:[ \t]::g'`
nodotsver=`echo $ver | sed -e 's:\.::g'`

for i in b s d; do
    rm -rf dists/pakk${nodotsver}${i}
    mkdir -p dists/pakk${nodotsver}${i}
done

here=`pwd`
srczip=${here}/pakke-${ver}.zip

# Make the source distribution.
stem=pakk${nodotsver}s
srcstem=${stem}

mkdir -p dists/${stem}/contrib
cd dists/${stem}/contrib

unzip -q ${srczip}
mv pakke-${ver} ${stem}

cd ${here}/dists/${stem}

copy_into_manifest ${here}/manifest/${stem}
kill_cvs
make_manifest manifest/${stem}.mft
make_zip ${here}/dists/${stem}.zip

cd ${here}

# Make the binary distribution.
stem=pakk${nodotsver}b
binstem=${stem}

make install prefix=${here}/dists/${stem}

cd dists/${stem}

# Remove bogus info directory.
rm info/dir

copy_into_manifest ${here}/manifest/${stem}
kill_cvs
make_manifest manifest/${stem}.mft
make_zip ${here}/dists/${stem}.zip

cd ${here}

# Make the documentation distribution.
stem=pakk${nodotsver}d
docstem=${stem}

mkdir -p dists/${stem}/contrib/pakke${nodotsver}
cd dists/${stem}/contrib/pakke${nodotsver}

# Don't recurse here, because we only want README, etc.; not
# the sub-directories like scripts.
cp -pv ${here}/dists/${binstem}/contrib/pakke${nodotsver}/* .

mkdir -p doc
cd doc
for i in ${here}/doc/*.dvi ${here}/doc/*.ps ${here}/doc/*.html; do
    cp -pv $i .
done

cd ${here}/dists/${stem}

copy_into_manifest ${here}/manifest/${stem}
kill_cvs
make_manifest manifest/${stem}.mft
make_zip ${here}/dists/${stem}.zip

cd ${here}
