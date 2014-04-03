//==================================================================================================
//
// File:    GeomSphere.h
// Author:  Jason Jackson
// Date:    December 5th, 2008
//
// A sphere representation in 3-space
//
//=================================================================================================

#ifdef GEOMSPHERE_H
#  error "Cannot include header more than once."
#endif
#define GEOMSPHERE_H

class Sphere2;
class Sphere3;

typedef Sphere2 Circle;

//=============================================================================
//
// A sphere in 2-space defined by the center and the radius of the sphere
//
//=============================================================================
class Sphere2
{
public:
    Sphere2();
    Sphere2( const Point2 & c, float32 r );

    static const Sphere2 Unit;

    union
    {
        struct{ Point2 center;  float32 radius; };
        struct{ float32 x, y, r; };
    };
};

//=============================================================================
//
// A sphere in 3-space defined by the center and the radius of the sphere
//
//=============================================================================
class Sphere3
{
public:
    Sphere3();
    Sphere3( const Point3 & c, float32 r );

    static const Sphere3 Unit;

    union
    {
        struct{ Point3 center;  float32 radius; };
        struct{ float32 x, y, z, r; };
    };
};
