// SCOPERES.CPP

// This is an example program from Chapter 2 of the C++ Tutorial. This
//     program demonstrates the scope resolution operator.

#include <iostream.h>

int amount = 123;    // A global variable

void main()
{
   int amount = 456; // A local variable 

   cout << ::amount; // Print the global variable
   cout << '\n';
   cout << amount;   // Print the local variable
}
