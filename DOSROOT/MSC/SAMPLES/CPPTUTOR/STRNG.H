// STRNG.H

// This is the final version of an example class from Chapter 5 of the
//     C++ Tutorial. This class performs dynamic allocation of memory,
//     allowing resizeable objects. It demonstrates a destructor, a
//     user-defined operator=, and a copy constructor.

#if !defined( _STRNG_H_ )

#define _STRNG_H_

#include <iostream.h>

// ------- A string class
class String
{
public:
   String();
   String( const char *s );
   String( char c, int n );
   String( const String &other );              // Copy constructor
   String &operator=( const String &other );   // Assignment operator
   void set( int index, char newchar );
   char get( int index ) const;
   int getLength() const;
   void display() const;
   void append( const char *addition );
   ~String();
private:
   int length;
   char *buf;
};

inline int String::getLength() const
{
    return length;
}

inline void String::display() const
{
    cout << buf;
}

#endif  // _STRNG_H_

