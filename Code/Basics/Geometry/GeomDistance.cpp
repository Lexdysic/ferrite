//=================================================================================================
//
// File:    GeomDistance.cpp
// Author:  Jason Jackson
// Date:    June 5, 2009
//
// Computes the shortest distance between objects
//
//=================================================================================================

#include "GeomPch.h"


//=============================================================================
float32 Distance (const Point2 & point, const Halfspace2 & hs)
{
    const Vector2 & v = point - hs.point;
    return Dot(hs.normal, v) / LengthSq(hs.normal);
}
