// FRAC1.H

// This is an example class from Chapter 8 of the C++ Tutorial. This
//     class demonstrates the overloaded binary + operator, the
//     overloaded unary - operator, and two user-defined conversions:
//     one using a conversion operator, and one using a single-argument
//     constructor. This class results in ambiguity errors when you
//     compile statements like a = b + 1234 (where a and b are Fraction
//     objects), because the compiler cannot decide which user-defined
//     conversion to use.

#if !defined( _FRAC1_H_ )

#define _FRAC1_H_

class Fraction
{
public:
    Fraction();
    Fraction( long num, long den = 1 );
    void display() const;
    operator float() const;
    friend Fraction operator+( const Fraction &first,
                               const Fraction &second );
    friend Fraction operator-( const Fraction &one );
private:
    static long gcf( long first, long second );
    long numerator,
         denominator;
};

#endif // _FRAC1_H_

