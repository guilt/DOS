// VARDECL.CPP

// This is an example program from Chapter 2 of the C++ Tutorial. This
//     program demonstrates the placement of variable declarations.

#include <iostream.h>

void main()
{
   for( int lineno = 0; lineno < 3; lineno++ )
   {
       int temp = 22;
       cout << "This is line number " << lineno
            << " and temp is " << temp << '\n';
   }
   if( lineno == 4 )   // lineno still accessible
       cout << "Oops\n";
   // Cannot access temp
}
