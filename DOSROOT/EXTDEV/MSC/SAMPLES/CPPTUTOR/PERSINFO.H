// PERSINFO.H

// This is an example class from Chapter 4 of the C++ Tutorial. This
//     class demonstrates member objects and the member-initializer
//     syntax for initializing a constant member object.

#if !defined( _PERSINFO_H_ )

#define _PERSINFO_H_

#include "date.h"

class PersonInfo
{
public:
    PersonInfo( const char *nm, const char *addr, int mn, int dy, int yr );
private:
   char name[30];
   char address[60];
   const Date birthday;     // Constant member object
};

#endif  // _PERSINFO_H_

