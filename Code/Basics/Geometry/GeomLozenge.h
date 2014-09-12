#ifdef GEOMLOZENGE_H
#  error "Cannot include header more than once."
#endif
#define GEOMLOZENGE_H

//*****************************************************************************
//
// Lozenge3
//
//*****************************************************************************

class Lozenge3
{
public:
    Lozenge3 ();
    Lozenge3 (const Point3 & center, const Vector3 & u, const Vector3 & v, float32 radius);

    Point3  center;
    union
    {
        struct{ Vector3 extent[2]; };
        struct{ Vector3 u, v; };
    };
    float32 radius;
};