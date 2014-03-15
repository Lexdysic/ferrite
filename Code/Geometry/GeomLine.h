//==================================================================================================
//
// File:    GeomLine.h
// Author:  Jason Jackson
// Date:    December 5th, 2008
//
// A line extends infinitly  along a vector in both directions and passes through a point
//
//=================================================================================================

#ifdef GEOMLINE_H
#  error "Cannot include header more than once."
#endif
#define GEOMLINE_H

//=============================================================================
//
// Represents a 3D line, defined by a point on the line and vector direction
//
//=============================================================================
class Line3
{
public:
    Line3();
    Line3( const p3 & origin, const v3 & direction );


    p3 origin;      //!< Any point on the line
    v3 direction;   //!< A vector direction of the line (need not be normalized)
};