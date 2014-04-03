//==================================================================================================
//
// File:    GeomEllipsoid.cpp
// Author:  Jason Jackson
// Date:    December 5th, 2008
//
// Represents a ellipoid in 3-space
//
//=================================================================================================

#include "GeomPch.h"

const Ellipsoid3 Ellipsoid3::Unit( Point3::Zero, Vector3::UnitX, Vector3::UnitY, Vector3::UnitZ );

//=============================================================================
Ellipsoid3::Ellipsoid3()
{
}

//=============================================================================
Ellipsoid3::Ellipsoid3( const Point3 & c, const Vector3 & u, const Vector3 & v, const Vector3 & w )
: center(c)
, u(u)
, v(v)
, w(w)
{
}