// REFDEMO.CPP

// This is an example program from Chapter 3 of the C++ Tutorial. This
//     program demonstrates reference variables.

#include <iostream.h>

void main()
{
   int actualint = 123;
   int &otherint = actualint;

   cout << '\n' << actualint;
   cout << '\n' << otherint;
   otherint++;
   cout << '\n' << actualint;
   cout << '\n' << otherint;
   actualint++;
   cout << '\n' << actualint;
   cout << '\n' << otherint;
}
