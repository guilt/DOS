#include <fastgraf.h>
#include <stdio.h>
#include <stdlib.h>

void main(void);

void main()
{
   int mode, old_mode;
   char string[5];

/* Ask for the video mode number */

   printf("Which video mode? ");
   scanf("%d",&mode);

/* Make sure the entered value is valid */

   if (mode < 0 || mode > 29) {
      printf("%d is not a valid video mode number.\n",mode);
      exit(1);
      }

/* Make sure the requested video mode is available */

   if (fg_testmode(mode,1) == 0) {
      printf("Mode %d is not available on this system.\n",mode);
      exit(1);
      }

/* Establish the video mode */

   old_mode = fg_getmode();
   fg_setmode(mode);

/* Perform mode-specific initializations */

   if (mode <= 3 || mode == 7)   /* text modes */
      fg_cursor(0);

   else if (mode == 4 || mode == 5) { /* CGA color modes */
      fg_palette(0,0);
      fg_defcolor(14,3);
      }

   else if (mode == 6) {         /* CGA two-color mode */
      fg_palette(0,14);
      fg_defcolor(14,1);
      }

   else if (mode == 11)          /* Hercules mode */
      fg_defcolor(14,1);

   else if (mode == 12)          /* Hercules low-res mode */
      fg_defcolor(14,3);

   else if (mode == 17) {        /* VGA two-color mode */
      fg_palette(1,14);
      fg_setrgb(14,63,63,21);
      fg_defcolor(14,1);
      }

/* Display a message that includes the video mode number */

   fg_setcolor(14);
   fg_text("I'm running in mode ",20);
   sprintf(string,"%d. ",mode);
   fg_text(string,3);

/* Wait for a keystroke */

   fg_waitkey();

/* Restore the original video mode and screen attributes */

   fg_setmode(old_mode);
   fg_reset();
}
