//==================================================================================================
//
// File:    GeomLine.cpp
// Author:  Jason Jackson
// Date:    December 5th, 2008
//
// A line extends infinitly  along a vector in both directions and passes through a point
//
//=================================================================================================

#include "GeomPch.h"

//=============================================================================
Line2::Line2 ()
{
}

//=============================================================================
Line2::Line2 (const Point2 & a, const Point2 & b) :
    origin(a),
    direction(b - a)
{
}

//=============================================================================
Line2::Line2 (const Point2 & origin, const Vector2 & direction) :
    origin(origin),
    direction(direction)
{
}



//=============================================================================
Line3::Line3 ()
{
}

//=============================================================================
Line3::Line3 (const Point3 & a, const Point3 & b) :
    origin(a),
    direction(b - a)
{
}

//=============================================================================
Line3::Line3 (const Point3 & origin, const Vector3 & direction) :
    origin(origin),
    direction(direction)
{
}