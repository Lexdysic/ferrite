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

const Ellipsoid3 Ellipsoid3::Unit( p3::Zero, v3::UnitX, v3::UnitY, v3::UnitZ );

//=============================================================================
Ellipsoid3::Ellipsoid3()
{
}

//=============================================================================
Ellipsoid3::Ellipsoid3( const p3 & c, const v3 & u, const v3 & v, const v3 & w )
: center(c)
, u(u)
, v(v)
, w(w)
{
}