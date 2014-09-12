#ifdef GEOMRAY_H
#  error "Cannot include header more than once."
#endif
#define GEOMRAY_H

//*****************************************************************************
//
// Ray2
//
//*****************************************************************************

class Ray2
{
public:
    Ray2 ();
    Ray2 (const Point2 & origin, const Vector2 & direction);

    Point2  origin;
    Vector2 direction;
};



//*****************************************************************************
//
// Ray3
//
//*****************************************************************************

class Ray3
{
public:
    Ray3 ();
    Ray3 (const Point3 & origin, const Vector3 & direction);

    Point3  origin;
    Vector3 direction;
};
