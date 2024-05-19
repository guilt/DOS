
# Free Pascal 

NAME=passmpl2

PC=fpc.exe

$(NAME).exe: $*.pas fpc2.mak
    $(PC) $*.pas
    pestub -s -n $*.exe ..\..\bin\dpmist32.bin

