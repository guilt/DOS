// FRAC1.CPP

#include "frac1.h"
#include <math.h>
#include <iostream.h>

// ----------- Default constructor
Fraction::Fraction()
{
    numerator = 0;
    denominator = 1;
}

// ----------- Constructor
Fraction::Fraction( long num, long den )
{
    int factor;

    if( den == 0 )
        den = 1;
    numerator = num;
    denominator = den;
    if( den < 0 )
    {
        numerator = -numerator;
        denominator = -denominator;
    }
    factor = gcf( num, den );
    if( factor > 1 )
    {
        numerator /= factor;
        denominator /= factor;
    }
}

// ----------- Function to print a Fraction
void Fraction::display() const
{
    cout << numerator << '/' << denominator;
}

// ----------- Conversion operator to float
Fraction::operator float() const
{
    return (float)numerator / (float)denominator;
}

// ----------- Overloaded + operator
Fraction operator+( const Fraction &first, const Fraction &second )
{
    long factor,
         mult1,
         mult2;

    factor = Fraction::gcf( first.denominator, second.denominator );
    mult1 = first.denominator / factor;
    mult2 = second.denominator / factor;

    return Fraction( first.numerator * mult2 + second.numerator * mult1,
                     first.denominator * mult2 );
}

// ----------- Overloaded unary - operator
Fraction operator-( const Fraction &one )
{
    return Fraction( -one.numerator, one.denominator );
}

// ----------- Greatest common factor
// computed using iterative version of Euclid's algorithm
long Fraction::gcf( long first, long second )
{
    int temp;

    first = labs( first );
    second = labs( second );

    while( second > 0 )
    {
        temp = first % second;
        first = second;
        second = temp;
    }

    return first;
}

