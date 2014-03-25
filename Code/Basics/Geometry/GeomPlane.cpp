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

const Plane2 Plane2::X(1.0f, 0.0f, 0.0f);
const Plane2 Plane2::Y(0.0f, 1.0f, 0.0f);

//=============================================================================
Plane2::Plane2 ()
{
}

//=============================================================================
Plane2::Plane2 (const Point2 & point, const Vector2 & normal)
{
    n = Normalize(normal);
    d = Dot(point, n);
}

//=============================================================================
Plane2::Plane2 (const Point2 & a, const Point2 & b)
{
    const Vector2 u = b - a;

    n = Normalize(Perpendicular(u));
    d = Dot(a, n);
}

//=============================================================================
Plane2::Plane2 (float32 a, float32 b, float32 d) :
    a(a),
    b(b),
    d(d)
{
}



//=============================================================================
const Plane3 Plane3::YZ(1.0f, 0.0f, 0.0f, 0.0f);
const Plane3 Plane3::XZ(0.0f, 1.0f, 0.0f, 0.0f);
const Plane3 Plane3::XY(0.0f, 0.0f, 1.0f, 0.0f);

//=============================================================================
Plane3::Plane3 ()
{
}

//=============================================================================
Plane3::Plane3 (const Point3 & point, const Vector3 & normal)
{
    n = Normalize(normal);
    d = -Dot(point, n);
}

//=============================================================================
Plane3::Plane3 (const Point3 & a, const Point3 & b, const Point3 & c)
{
    const Vector3 u = b - a;
    const Vector3 v = c - a;

    ASSERT(!IsParallel(u,v));

    n = Normalize(Cross(u, v));
    d = -Dot(a, n);
}

//=============================================================================
Plane3::Plane3 (float32 a, float32 b, float32 c, float32 d) :
    a(a),
    b(b),
    c(c),
    d(d)
{
}
