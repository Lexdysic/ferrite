//==================================================================================================
//
// File:    GeomTriangle.h
// Author:  Jason Jackson
// Date:    December 5th, 2008
//
// A triangle in space
//
//=================================================================================================

#ifdef GEOMTRIANGLE_H
#  error "Cannot include header more than once."
#endif
#define GEOMTRIANGLE_H

//=============================================================================
//
// A triangle defined by the three corner points
//
//=============================================================================
class Triangle3
{
public:
    Triangle3();
    Triangle3( const p3 & a, const p3 & b, const p3 & c );

    union 
    {
        struct { p3 p[3]; };
        struct { p3 a, b, c; };
    };
};
