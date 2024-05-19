
# sample for Pascal Pro (http://www.cyrogen.com/pascalpro)
# before running this makefile change 2 lines in file PPRO.SRC:
#
# STUBER='STUBIT'
# STUBEROPTIONS='$exefile$'
#
# to:
#
# STUBER='PESTUB'
# STUBEROPTIONS='-n -s -x $exefile$ dpmist32.bin'
#
# please note that Pascal Pro creates true dos extended source,
# so only DPMILD32.exe is required to run such apps, no need for
# the Win32 emulation dlls.

NAME=passmpl1

# Pascal Pro
# name of compiler:
PC=ppro.exe

$(NAME).exe: $*.pas ppro1.mak
    $(PC) $*.pas

