#include "GeomPch.h"

//*****************************************************************************
//
// Triangle2
//
//*****************************************************************************

//=============================================================================
Triangle2::Triangle2 (const Point2 & a, const Point2 & b, const Point2 & c) :
    a(a),
    b(b),
    c(c)
{
}

//=============================================================================
Geometry::EWinding Triangle2::ComputeWiding () const
{
    const float32 cross = Cross(b - a, c - a);
    if (cross > Math::Epsilon)
        return Geometry::EWinding::CounterClockwise;
    if (cross < Math::Epsilon)
        return Geometry::EWinding::Clockwise;
    return Geometry::EWinding::Invalid;
}

//=============================================================================
float32 Triangle2::ComputeArea () const
{
    const Plane2 plane(a, b);
    const float32 height = Distance(c, plane);
    const float32 width  = Distance(a, b);
    return 0.5f * height * width;
}

//=============================================================================
Point2 Triangle2::ComputeCentroid () const
{
    Vector2 v = Vector2::Zero;
    v += Vector2(a);
    v += Vector2(a);
    v += Vector2(a);
    v /= 3.0f;
    return Point2(v);
}


//*****************************************************************************
//
// Triangle3
//
//*****************************************************************************

//=============================================================================
Triangle3::Triangle3 (const Point3 & a, const Point3 & b, const Point3 & c) :
    a(a),
    b(b),
    c(c)
{
}