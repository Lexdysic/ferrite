//==================================================================================================
//
// File:    GeomEllipsoid.h
// Author:  Jason Jackson
// Date:    December 5th, 2008
//
// Represents a ellipoid in 3-space
//
//=================================================================================================

#ifdef GEOMELLIPSOID_H
#  error "Cannot include header more than once."
#endif
#define GEOMELLIPSOID_H

//=============================================================================
//
// An ellipse defined in 3-space, defined by a center point and three orthnormal
// axis vectors.
//
//=============================================================================
class Ellipsoid3
{
public:
    Ellipsoid3();
    Ellipsoid3( const Point3 & c, const Vector3 & u, const Vector3 & v, const Vector3 & w );

    static const Ellipsoid3 Unit;

    Point3 center;
    Vector3 u, v, w;
};
