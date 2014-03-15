//==================================================================================================
//
// File:    GeomPlane.cpp
// Author:  Jason Jackson
// Date:    December 5th, 2008
//
// A plane represented in the Ax + By + Cz + D = 0 style
//
//=================================================================================================

#include "GeomPch.h"

const Plane2 Plane2::X( 1.0f, 0.0f, 0.0f );
const Plane2 Plane2::Y( 0.0f, 1.0f, 0.0f );

//=============================================================================
Plane2::Plane2()
{
}

//=============================================================================
Plane2::Plane2( const p2 & point, const v2 & normal )
{
    n = Normalize(normal);
    d = Dot(point, n);
}

//=============================================================================
Plane2::Plane2( const p2 & a, const p2 & b )
{
    v2 u = b - a;

    n = Normalize( v2(u.y, -u.x) );
    d = -Dot(a, n);
}

//=============================================================================
Plane2::Plane2( float32 a, float32 b, float32 d )
: a(a)
, b(b)
, d(d)
{
}



const Plane3 Plane3::YZ( 1.0f, 0.0f, 0.0f, 0.0f );
const Plane3 Plane3::XZ( 0.0f, 1.0f, 0.0f, 0.0f );
const Plane3 Plane3::XY( 0.0f, 0.0f, 1.0f, 0.0f );

//=============================================================================
Plane3::Plane3()
{
}

//=============================================================================
Plane3::Plane3( const p3 & point, const v3 & normal )
{
    n = Normalize(normal);
    d = -Dot(point, n);
}

//=============================================================================
Plane3::Plane3( const p3 & a, const p3 & b, const p3 & c )
{
    v3 u = b - a;
    v3 v = c - a;

    assert( !Parallel(u,v) );

    n = Normalize( Cross(u, v) );
    d = -Dot(a, n);
}

//=============================================================================
Plane3::Plane3( float32 a, float32 b, float32 c, float32 d )
: a(a)
, b(b)
, c(c)
, d(d)
{
}
