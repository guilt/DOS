// DATE.H

// This is the final version of an example class from Chapter 4 of the
//     C++ Tutorial. This class demonstrates an overloaded constructor,
//     inline member functions, and const member functions.

#if !defined( _DATE_H_ )

#define _DATE_H_

class Date
{
public:
   Date();                          // Default constructor
   Date( int mn, int dy, int yr );  // Constructor
                                    // Member functions:
   int getMonth() const;            //   Get month - read only
   int getDay() const;              //   Get day - read only 
   int getYear() const;             //   Get year - read only
   void setMonth( int mn );         //   Set month
   void setDay( int dy );           //   Set day
   void setYear( int yr );          //   Set year
   void display() const;            //   Print date - read only
   ~Date();                         // Destructor
private:
   int month, day, year;            // Private data members
};

// some useful functions
inline int max( int a, int b )
{
    if( a > b ) return a;
    return b;
}

inline int min( int a, int b )
{
    if( a < b ) return a;
    return b;
}

inline int Date::getMonth() const
{
    return month;
}

inline int Date::getDay() const
{
    return day;
}

inline int Date::getYear() const
{
    return year;
}

#endif  // _DATE_H_

