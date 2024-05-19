
# create a stand-alone HX DOS binary in PE format.
# uses CC386's C RTL for DOS.

NAME=SAMPLED

$(NAME).exe: $(NAME).obj
    valx /PE /MAP /NCI /STB:(..\..\Bin\loadpe.bin) c0doswhx.obj $(NAME).obj,$(NAME).exe,,cldos.lib;
    ..\..\Bin\patchpe $(NAME).exe

$(NAME).obj: sample.c
   cc386 /c /o$(NAME).obj sample.c
