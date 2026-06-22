// SAVINGS.CPP
#include "savings.h"
#include <string.h>

// Initialize private static member at file scope
float SavingsAccount::currentRate = 0.0001;

SavingsAccount::SavingsAccount( const char *nm, float tl )
{
    strncpy( name, nm, 30 );
    name[29] = '\0';
    total = tl;
}
