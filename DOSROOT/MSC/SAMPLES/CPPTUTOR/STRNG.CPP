// STRNG.CPP

#include "strng.h"
#include <string.h>

// Default constructor
String::String()
{
    buf = 0;
    length = 0;
}

// ---------- Constructor that takes a const char *
String::String( const char *s )
{
    length = strlen( s );
    buf = new char[length + 1];
    strcpy( buf, s );
}

// ---------- Constructor that takes a char and an int
String::String( char c, int n )
{
    length = n;
    buf = new char[length + 1];
    memset( buf, c, length );
    buf[length] = '\0';
}

// ----------- Copy constructor
String::String( const String &other )
{
    length = other.length;
    buf = new char[length + 1];
    strcpy( buf, other.buf );
}

String &String::operator=( const String &other )
{
    if( &other == this )
        return *this;
    delete buf;
    length = other.length;
    buf = new char[length + 1];
    strcpy( buf, other.buf );
    return *this;
}

// ---------- Set a character in a String
void String::set( int index, char newchar )
{
    if( (index > 0) && (index <= length) )
        buf[index - 1] = newchar;
}

// ---------- Get a character in a String
char String::get( int index ) const
{
    if( (index > 0) && (index <= length) )
        return buf[index - 1];
    else
        return 0;
}

void String::append( const char *addition )
{
    char *temp;

    length += strlen( addition );
    temp = new char[length + 1];   // Allocate new buffer
    strcpy( temp, buf );           // Copy contents of old buffer
    strcat( temp, addition );      // Append new string
    delete buf;                    // Deallocate old buffer
    buf = temp;
}

// ---------- Destructor for a String
String::~String()
{
    delete buf;   // Works even for empty String; delete 0 is safe
}

