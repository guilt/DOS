Rem fix to run the tppatch program on NT
echo g>inn
echo q>>inn
debug tppatch.exe %1 <inn
del inn
tppatch.exe
