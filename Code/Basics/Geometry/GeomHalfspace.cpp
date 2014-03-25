//==================================================================================================
//
// File:    GeomHalfspace.cpp
// Author:  Jason Jackson
// Date:    December 5th, 2008
//
// Represents an object which consumes half of 3-space
//
//=================================================================================================

#include "GeomPch.h"


Halfspace2::Halfspace2 (const Point2 & point, const Vector2 & outwardNormal) :
    point(point),
    normal(outwardNormal)
{
}


Halfspace3::Halfspace3 (const Point3 & point, const Vector3 & outwardNormal) :
    point(point),
    normal(outwardNormal)
{
}