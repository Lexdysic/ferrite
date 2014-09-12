#ifdef GEOMELLIPSOID_H
#  error "Cannot include header more than once."
#endif
#define GEOMELLIPSOID_H

//*****************************************************************************
//
// Ellipsoid
//
//*****************************************************************************
class Ellipsoid3
{
public:
    Ellipsoid3 ();
    Ellipsoid3 (const Point3 & center, const Vector3 & u, const Vector3 & v, const Vector3 & w);

    static const Ellipsoid3 Unit;

    Point3  center;
    Vector3 u;
    Vector3 v;
    Vector3 w;
};
