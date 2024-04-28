//
// ANNUITY2.C - Generate annuity table.
// Corrrected and formatted version of PWB Tutorial program
//
#include <stdio.h>
#include <math.h>

void main( void )
{
    float Principal, Rate, Pmt, RatePct, PerInterest, PerPrin;
    int Nper, ActNper, Period;

    //
    // Get input from the user.
    //

    printf( "\nEnter Present Value: " );
    scanf ( "%f", &Principal );
    printf( "\nEnter Interest Rate in Percent: " );
    scanf ( "%f", &Rate );
    printf( "\nEnter Number of Periods in Years: " );
    scanf ( "%i", &Nper );

    //
    //  Calculate periodic percentage as a fraction (RatePct),
    //  number of periods in months (ActNper). Then, calculate
    //  the monthly payment (Pmt).
    //

    RatePct = Rate / 1200.0;
    ActNper = Nper * 12;
    Pmt = Principal * (RatePct / (1.0 - (1.0 /
          pow( 1.0 + RatePct, ActNper ))));

    //
    //  Print a summary of the annuity
    //
    printf(
        "\n\n"
        "Principal:       %13.2f\n"
        "Interest Rate:   %13.2f\n"
        "Number of Years: %13i\n"
        "Monthly Payment: %13.2f\n"
        "Total Payments:  %13.2f\n"
        "Total Interest:  %13.2f\n\n\n",
        Principal, Rate, Nper, Pmt,
        Pmt * (float)Nper * 12.0,
        Pmt * (float)Nper * 12.0 - Principal );

    //
    //  Print headings of the amortization table.
    //
    printf( "Period Year   Principal Interest\n"
            "------ ------ --------- --------\n" );

    //
    //  Loop on the number of periods, printing the period, year,
    //  interest portion and principal portion of each payment.
    //

    for( Period = 1; Period <= ActNper; Period++ )
    {
        PerInterest = Principal * RatePct;
        PerPrin = Pmt - PerInterest;
        printf( "%6d %6d %9.2f %9.2f\n",
            Period, Period / 12, PerPrin, PerInterest );
        Principal = Principal - PerPrin;
    }

}
