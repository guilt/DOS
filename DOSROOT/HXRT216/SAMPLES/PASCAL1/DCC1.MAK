
# for Delphi. Adjust path for units below!

NAME=passmpl1

PC=dcc32.exe -GD -CC -U\delphi7\lib

$(NAME).exe: $*.pas dcc1.mak
    $(PC) $*.pas
    pestub -s -n $*.exe ..\..\bin\dpmist32.bin

