
# Free Pascal 

NAME=passmpl1

PC=fpc.exe

$(NAME).exe: $*.pas fpc1.mak
    $(PC) $*.pas
    pestub -s -n $*.exe ..\..\bin\dpmist32.bin

