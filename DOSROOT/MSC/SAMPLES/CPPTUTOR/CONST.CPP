// CONST.CPP

// This is an example program from Chapter 2 of the C++ Tutorial. This
//     program demonstrates the const qualifier.

#include <iostream.h>

void main()
{
   const int SIZE = 5;
   char cs[SIZE];

   cout << "The size of cs is " << sizeof cs;
}
