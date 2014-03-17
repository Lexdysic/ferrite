//==================================================================================================
//
// File:    GeomRect.cpp
// Author:  Jason Jackson
// Date:    December 5th, 2008
//
// Represents a finite 2-d rectagular plane in 3-space
//
//=================================================================================================

#include "GeomPch.h"

//=============================================================================
Rect3::Rect3()
{
}

//=============================================================================
Rect3::Rect3 (const Point3 & center, const Vector3 & x, const Vector3 & y) :
    center(center)
{
    u[0] = x;
    u[1] = y;
    extent[0] = Normalize2( u[0] );
    extent[1] = Normalize2( u[1] );
    
}

//=============================================================================
Rect3::Rect3 (const Point3 & center, const Vector3 & unitX, const Vector3 & unitY, const Vector2 & extent) :
    center(center),
    extent(extent)
{
    assert(Normalized(unitX));
    assert(Normalized(unitY));

    u[0] = unitX;
    u[1] = unitY;
}