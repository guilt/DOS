#include <fastgraf.h>
#include <io.h>
#include <stdio.h>
#include <stdlib.h>

void main(void);

char pixel_runs[20000];

void main()
{
   FILE *stream;
   int file_size, run_count;
   int old_mode, new_mode;

   new_mode = fg_bestmode(320,200,1);
   if (new_mode < 0 || new_mode == 12) {
      printf("This program requires a 320 ");
      printf("x 200 color graphics mode.\n");
      exit(1);
      }

   old_mode = fg_getmode();
   fg_setmode(new_mode);

   stream = fopen("coral.spr","rb");
   file_size = (int)(filelength(fileno(stream)));
   fread(pixel_runs,sizeof(char),file_size,stream);
   fclose(stream);
   run_count = file_size / 2;
   fg_move(0,199);
   fg_display(pixel_runs,run_count,320);
   fg_waitkey();

   stream = fopen("coral.ppr","rb");
   file_size = (int)(filelength(fileno(stream)));
   fread(pixel_runs,sizeof(char),file_size,stream);
   fclose(stream);
   run_count = file_size / 3 * 2;
   fg_erase();
   fg_displayp(pixel_runs,run_count,320);
   fg_waitkey();

   fg_setmode(old_mode);
   fg_reset();
}
