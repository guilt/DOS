/*------------------------------------------------------------------------*/
/*                                                                        */
/*  SHDDEL.H                                                              */
/*                                                                        */
/*  Copyright (c) 1991, 1994 Borland International                        */
/*  All Rights Reserved                                                   */
/*                                                                        */
/*------------------------------------------------------------------------*/

#if !defined( CLASSLIB_SHDDEL_H )
#define CLASSLIB_SHDDEL_H

#if !defined( CLASSLIB_DEFS_H )
#include <classlib/defs.h>
#endif

#pragma option -Vo-
#if defined( BI_CLASSLIB_NO_po )
#pragma option -po-
#endif

class TShouldDelete
{

public:

    enum DeleteType { NoDelete, DefDelete, Delete };

    TShouldDelete( DeleteType dt = Delete )
        {
        OwnsElements( dt );
        }

    int OwnsElements()
        {
        return ShouldDelete == Delete;
        }

    void OwnsElements( int del )
        {
        ShouldDelete = (del == 0) ? NoDelete : Delete;
        }

#if defined( BI_OLDNAMES )
    int ownsElements() { return OwnsElements(); }
    void ownsElements( int del ) { OwnsElements(del); }
#endif  // BI_OLDNAMES

    int DelObj( DeleteType dt )
        {
        return dt == Delete || (dt==DefDelete && ShouldDelete==Delete);
        }

#if defined( BI_OLDNAMES )
    int delObj( DeleteType dt ) { return DelObj(dt); }
#endif  // BI_OLDNAMES

private:

    DeleteType ShouldDelete;

};

#if defined( BI_OLDNAMES )
#define BI_ShouldDelete TShouldDelete
#endif

#if defined( BI_CLASSLIB_NO_po )
#pragma option -po.
#endif

#pragma option -Vo.

#endif  // CLASSLIB_SHDDEL_H

