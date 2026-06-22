// FRAC2.H

// This is an example class from Chapter 8 of the C++ Tutorial. This
//     class demonstrates the overloaded binary + operator using three
//     separate functions, the overloaded unary - operator, and two
//     user-defined conversions: one using a conversion operator, and
//     one using a single-argument constructor. This class avoids the
//     ambiguity errors that FRAC1.H causes for statements like
//     a = b + 1234 (where a and b are Fraction objects). The use
//     of three separate operator+ functions resolves the ambiguity.

#if !defined( _FRAC2_H_ )

#define _FRAC2_H_

class Fraction
{
public:
    Fraction();
    Fraction( long num, long den = 1 );
    void display() const;
    operator float() const;
    friend Fraction operator+( const Fraction &first,
                               const Fraction &second );
    friend Fraction operator+( long first,
                               const Fraction &second );
    friend Fraction operator+( const Fraction &first,
                               long second );
    friend Fraction operator-( const Fraction &one );
private:
    static long gcf( long first, long second );
    long numerator,
         denominator;
};

#endif // _FRAC2_H_

