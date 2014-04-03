//==================================================================================================
//
// File:    GeomRay.cpp
// Author:  Jason Jackson
// Date:    December 5th, 2008
//
// A line which starts a point in space and extends infinitely in one direction
//
//=================================================================================================

#include "GeomPch.h"

//=============================================================================
Ray2::Ray2() 
{
}

//=============================================================================
Ray2::Ray2( const Point2 & origin, const Vector2 & direction )
: origin(origin)
, direction(direction)
{
}

//=============================================================================
Ray3::Ray3() 
{
}

//=============================================================================
Ray3::Ray3( const Point3 & origin, const Vector3 & direction )
: origin(origin)
, direction(direction)
{
}