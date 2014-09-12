#ifdef GEOMCAPSULE_H
#  error "Cannot include header more than once."
#endif
#define GEOMCAPSULE_H

//*****************************************************************************
//
// Capsule3
//
//*****************************************************************************

class Capsule3
{
public:
    Capsule3();
    Capsule3( const Point3 & a, const Point3 & b, float32 r );

    union
    {
        struct { Segment3 seqment;  float32 radius; };
        struct { Point3 a, b;       float32 r; };
    };
};
