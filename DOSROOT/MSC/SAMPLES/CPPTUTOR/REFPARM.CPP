// REFPARM.CPP

// This is an example program from Chapter 3 of the C++ Tutorial. This
//     program uses a function with reference parameters for reducing
//     overhead and eliminating pointer notation.

#include <iostream.h>

// ---------- A big structure
struct bigone
{
   int serno;
   char text[1000];   // A lot of chars
} bo = { 123, "This is a BIG structure" };

// -- Three functions that have the structure as a parameter
void valfunc( bigone v1 );          // Call by value
void ptrfunc( const bigone *p1 );   // Call by pointer
void reffunc( const bigone &r1 );   // Call by reference

void main()
{
   valfunc( bo );   // Passing the variable itself
   ptrfunc( &bo );  // Passing the address of the variable
   reffunc( bo );   // Passing a reference to the variable
}

// ---- Pass byÿvalue
void valfunc( bigone v1 )
{
   cout << '\n' << v1.serno;
   cout << '\n' << v1.text;
}
// ---- Pass by pointer
void ptrfunc( const bigone *p1 )
{
   cout << '\n' << p1->serno;     // Pointer notation
   cout << '\n' << p1->text;
}

// ---- Pass by reference
void reffunc( const bigone &r1 )
{
   cout << '\n' << r1.serno;       // Reference notation
   cout << '\n' << r1.text;
}
