// PERSINFO.CPP

#include "persinfo.h"
#include <string.h>

PersonInfo::PersonInfo( const char *nm, const char *addr, int mn, int dy, int yr )
    : birthday( mn, dy, yr ) // Member-initializer
{
    strncpy( name, nm, 30 );
    name[29] = '\0';
    strncpy( address, addr, 60 );
    name[59] = '\0';
}

