// LINKAGE.CPP

// This is an example program from Chapter 2 of the C++ Tutorial. This
//     program demonstrates the use of a linkage specification.

#include <iostream.h>
#include <stdlib.h>
#include <string.h>

// ------ Prototype for a C function
extern "C" int comp( const void *a, const void *b );

void main()
{
   // --------- Array of string pointers to be sorted
   static char *brothers[] = {
      "Frederick William",
      "Joseph Jensen",
      "Harry Alan",
      "Walter Elsworth",
      "Julian Paul"
   };
   // ---------- Sort the strings in alphabetical order
   qsort( brothers, 5, sizeof(char *), comp );
   // ---------- Display the brothers in sorted order
   for( int i = 0; i < 5; i++ )
      cout << '\n' << brothers[i];
}

// ---------- A function compiled with C linkage
extern "C"
{
   int comp( const void *a, const void *b )
   {
      return strcmp( *(char **)a, *(char **)b );
   }
}
