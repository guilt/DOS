// REFADDR.CPP

// This is an example program from Chapter 3 of the C++ Tutorial. This
//     program shows that the address of a variable and the address of
//     a reference to that variable are the same.

#include <iostream.h>

void main()
{
   int actualint = 123;
   int &otherint = actualint;

   cout << &actualint << ' ' << &otherint;
}
