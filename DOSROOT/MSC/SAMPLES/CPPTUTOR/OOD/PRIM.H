/*********************************************************************

 FILE: PRIM.H

 Defines primitive types Point and Rect.

**********************************************************************/

#if !defined( _PRIM_H_ )

#define _PRIM_H_

#define self (*this)

#define max(a,b) ((a) > (b) ? (a) : (b))
#define min(a,b) ((a) < (b) ? (a) : (b))


/*********************************************************************

 Point

 Describes two-dimensional points.

 Public Interface:

    Point - constructor taking no args
    Point - constructor taking two integers
    x, y - coordinates
    operator==, operator!= - equality test
    operator+, operator+= - addition
    operator-, operator-= - subtraction
    operator*, operator*= - multiplication (scale)
    operator/, operator/= - division (scale)


*********************************************************************/


class Point
{
public:
    Point();
    Point( int xT, int yT );
    // use default copy-constructor (memberwise initialization)
    // use default operator= (memberwise assignment)
    int   operator==( Point pt ) const;
    int   operator!=( Point pt ) const;
    Point operator+( Point pt ) const;
    Point operator+=( Point pt );
    Point operator-( Point pt ) const;
    Point operator-=( Point pt );
    Point operator*( Point pt ) const;
    Point operator*=( Point pt );
    Point operator/( Point pt ) const;
    Point operator/=( Point pt );

// data members
    int   x;
    int   y;
};

inline Point::Point()
{
    x = y = 0;
}

inline Point::Point( int xT, int yT )
{
    x = xT;
    y = yT;
}

inline int Point::operator==( Point pt ) const
{
    return (x == pt.x && y == pt.y);
}

inline int Point::operator!=( Point pt ) const
{
    return (x != pt.x || y != pt.y);
}

#define _PointOp(_op_)  \
inline Point Point::operator _op_ ( Point pt ) const \
    { return Point(x _op_ pt.x, y _op_ pt.y); }      \
inline Point Point::operator _op_##= ( Point pt )    \
    { x _op_##= pt.x; y _op_##= pt.y; return self; }

_PointOp(+)
_PointOp(-)
_PointOp(*)
_PointOp(/)


/**********************************************************************

 Rect

 Describes rectangles.

 Public Interface:

    Rect - constructor taking no args
    Rect - constructor taking four integers
    left, right, top, bottom - coordinates
    width, length - return dimension
    operator==, operator!= - equality test
    isEmpty - tests for null rectangle
    Contains - tests if point is within rectangle border
    operator-, operator-=,
    operator+, operator+= - offset rectangle by a vector (use Point)
    operator&, operator&= - intersection of two rectangles
    operator|, operator|= - union of two rectangles

***********************************************************************/

class Rect
{
public:
    Rect();
    Rect( int leftT, int topT, int rightT, int bottomT );
    Rect( Point topLeft, Point bottomRight );
    // use default copy-constructor (memberwise initialization)
    // use default operator= (memberwise assignment)
    int  width() const;
    int  height() const;
    int  operator==( const Rect& r ) const;
    int  operator!=( const Rect& r ) const;
    int  isEmpty() const;
    int  Contains( Point pt ) const;
    Rect operator-( Point pt ) const;
    Rect operator-=( Point pt );
    Rect operator+( Point pt ) const;
    Rect operator+=( Point pt );
    Rect operator&( const Rect& other ) const;
    Rect operator&=( const Rect& other );
    Rect operator|( const Rect& other ) const;
    Rect operator|=( const Rect& other );

// data members
    int  left;
    int  top;
    int  right;
    int  bottom;
};

inline Rect::Rect()
{
    left = top = right = bottom = 0;
}

// construct from two points (NOT x,y,dx,dy !!!)
inline Rect::Rect( int leftT, int topT, int rightT, int bottomT )
{
    left = leftT;
    top = topT;
    right = rightT;
    bottom = bottomT;
}

inline Rect::Rect( Point topLeft, Point bottomRight )
{
    left = topLeft.x;
    top = topLeft.y;
    right = bottomRight.x;
    bottom = bottomRight.y;
}

inline int Rect::width() const
{
    return right - left;
}

inline int Rect::height() const
{
    return bottom - top;
}


inline int Rect::operator==( const Rect& r ) const
{
    return( left == r.left   &&
            top == r.top     &&
            right == r.right &&
            bottom == r.bottom );
}

inline int Rect::operator!=( const Rect& r ) const
{
    return( left != r.left   ||
            top != r.top     ||
            right != r.right ||
            bottom != r.bottom);
}

inline int Rect::isEmpty() const
{
    return (left >= right || top >= bottom);
}

inline int Rect::Contains( Point pt ) const
{
    return( pt.x >= left  &&
            pt.x <= right &&
            pt.y >= top   &&
            pt.y <= bottom);
}


#endif // _PRIM_H_
