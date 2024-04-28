// SAVINGS.H

// This is an example class from Chapter 6 of the C++ Tutorial. This
//     class demonstrates static data members and static member
//     functions.

#if !defined( _SAVINGS_H_ )

#define _SAVINGS_H_

#include <iostream.h>

class SavingsAccount
{
public:
    SavingsAccount( const char *nm, float tl );
    void display() const;
    void earnInterest() { total += currentRate * total; }
    static void setInterest( float newValue )
         { currentRate = newValue; }   // Static member function
private:
    char name[30];
    float total;
    static float currentRate;          // Static data member
};

inline void SavingsAccount::display() const
{
    cout << name << ' ' << total;
}

#endif  // _SAVINGS_H_

