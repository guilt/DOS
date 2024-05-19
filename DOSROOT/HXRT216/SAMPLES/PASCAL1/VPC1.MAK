
# Virtual Pascal 
# adjust paths for units and libs below!

NAME=passmpl1

PC=vpc.exe -U\vp21\units.w32 -L\vp21\lib.w32

$(NAME).exe: $*.pas vpc1.mak
    $(PC) $*.pas
    pestub -s -n $*.exe ..\..\bin\dpmist32.bin

