//==================================================================================================
//
// File:    GeomSphere.cpp
// Author:  Jason Jackson
// Date:    December 5th, 2008
//
// A sphere in 3-space represented by its center and a radius
//
//=================================================================================================

#include "GeomPch.h"

const Sphere2 Sphere2::Unit( Point2::Zero, 1.0f );
const Sphere3 Sphere3::Unit( Point3::Zero, 1.0f );

//=============================================================================
Sphere2::Sphere2()
{
}

//=============================================================================
Sphere2::Sphere2( const Point2 & c, float32 r )
: center(c)
, radius(r)
{
}

//=============================================================================
Sphere3::Sphere3()
{
}

//=============================================================================
Sphere3::Sphere3( const Point3 & c, float32 r )
: center(c)
, radius(r)
{
}
