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
    Ellipsoid3( const p3 & c, const v3 & u, const v3 & v, const v3 & w );

    static const Ellipsoid3 Unit;

    p3 center;
    v3 u, v, w;
};
