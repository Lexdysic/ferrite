//==================================================================================================
//
// File:    GeomCapsule.cpp
// Author:  Jason Jackson
// Date:    December 5th, 2008
//
// Shape which defines a cylindercal objective with spherical endcaps
//
//=================================================================================================

#include "GeomPch.h"

//=============================================================================
Capsule3::Capsule3()
{
}

//=============================================================================
Capsule3::Capsule3( const Point3 & p1, const Point3 & p2, float32 r )
: a(p1)
, b(p2)
, radius(r)
{
}