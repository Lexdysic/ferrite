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
Line3::Line3()
{
}

//=============================================================================
Line3::Line3( const p3 & origin, const v3 & direction )
: origin(origin)
, direction(direction)
{
}