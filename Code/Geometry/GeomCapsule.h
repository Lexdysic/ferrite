//==================================================================================================
//
// File:    GeomCapsule.h
// Author:  Jason Jackson
// Date:    December 5th, 2008
//
// Shape which defines a cylindercal objective with spherical endcaps
//
//=================================================================================================

#ifdef GEOMCAPSULE_H
#  error "Cannot include header more than once."
#endif
#define GEOMCAPSULE_H

class Capsule3
{
public:
    Capsule3();
    Capsule3( const p3 & a, const p3 & b, float32 r );

    union
    {
        struct { Segment3 seqment;  float32 radius; };
        struct { Point3 a, b;       float32 r; };
    };
};
