
# PowerBasic sample

NAME=pbsample

PBC=Pbcc.exe

$(NAME).exe: $*.bas Makefile
    $(PBC) $*.bas
    pestub -s -n $*.exe ..\..\bin\dpmist32.bin

