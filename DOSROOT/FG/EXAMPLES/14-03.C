#include <fastgraf.h>
#include <stdio.h>

void main(void);

void main()
{
   if (fg_capslock())
      printf("CapsLock is on.\n");
   else
      printf("CapsLock is off.\n");

   if (fg_numlock())
      printf("NumLock is on.\n");
   else
      printf("NumLock is off.\n");

   if (fg_scrlock())
      printf("ScrollLock is on.\n");
   else
      printf("ScrollLock is off.\n");
}
