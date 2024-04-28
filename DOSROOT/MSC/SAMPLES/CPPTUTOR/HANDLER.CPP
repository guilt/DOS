// HANDLER.CPP

// This is an example program from Chapter 6 of the C++ Tutorial. This
//     program demonstrates free store exhaustion and the
//     _set_new_handler function.

#include <iostream.h>
#include <new.h>
#include <stdlib.h>

int all_gone( size_t size )
{
   cerr << "The free store is empty\n";
   exit( -1 );
   return 0;
}

void main()
{
   _set_new_handler( all_gone );
   long total = 0;
   while( 1 )
   {
      char *gobble = new char[10000];
      total += 10000;
      cout << "Got 10000 for a total of " << total << '\n';
   }
}
