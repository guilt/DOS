/**********************************************************************

   FILE: PRIM.CPP

**********************************************************************/

#include "prim.h"


// OffsetRect by a Point (interpeted as a vector)

Rect Rect::operator+( Point pt ) const
{
    return Rect(left + pt.x, top + pt.y,
                right + pt.x, bottom + pt.y);
}

Rect Rect::operator+=( Point pt )
{
    left += pt.x;
    right += pt.x;
    top += pt.y;
    bottom += pt.y;
    return self;
}

Rect Rect::operator-( Point pt ) const
{
    return Rect(left - pt.x, top - pt.y,
                right - pt.x, bottom - pt.y);
}

Rect Rect::operator-=(Point pt)
{
    left -= pt.x;
    right -= pt.x;
    top -= pt.y;
    bottom -= pt.y;
    return self;
}


// intersection of two rectangles

Rect Rect::operator&( const Rect& other ) const
{
    return Rect( max( left, other.left ),
                 max( top, other.top ),
                 min( right, other.right ),
                 min( bottom, other.bottom ) );
}

Rect Rect::operator&=( const Rect& other )
{
    left = max( left, other.left );
    top = max( top, other.top );
    right = min( right, other.right );
    bottom = min( bottom, other.bottom );
    return self;
}

// union of two rectangles

Rect Rect::operator|( const Rect& other ) const
{
    return Rect( min( left, other.left ),
                 min( top, other.top ),
                 max( right, other.right ),
                 max( bottom, other.bottom ) );
}

Rect Rect::operator|=( const Rect& other )
{
    left = min( left, other.left );
    top = min( top, other.top );
    right = max( right, other.right );
    bottom = max( bottom, other.bottom );
    return self;
}

