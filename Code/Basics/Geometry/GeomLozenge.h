//==================================================================================================
//
// File:    GeomLozenge.h
// Author:  Jason Jackson
// Date:    December 5th, 2008
//
// A lozenge represents a sphere swept rectangle in space
//
//=================================================================================================

#ifdef GEOMLOZENGE_H
#  error "Cannot include header more than once."
#endif
#define GEOMLOZENGE_H

//=============================================================================
//
// A lozenge in 3-space
//
//=============================================================================
class Lozenge3
{
public:
    Lozenge3();
    Lozenge3( const Point3 & center, const Vector3 & u, const Vector3 & v, float32 radius );

    Point3  center;
    union
    {
        struct{ Vector3 extent[2]; };
        struct{ Vector3 u, v; };
    };
    float32 radius;
};