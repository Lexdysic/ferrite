#ifdef GEOMRECT_H
#  error "Cannot include header more than once."
#endif
#define GEOMRECT_H

//*****************************************************************************
//
// Rect3
//
//*****************************************************************************

class Rect3
{
public: // Construction

    Rect3 ();
    Rect3 (const Point3 & center, const Vector3 & x, const Vector3 & y);
    Rect3 (const Point3 & center, const Vector3 & unitX, const Vector3 & unitY, const Vector2 & extent);

public: // Data

    Point3 center;
    Vector3 u[2];
    Vector2 extent;
};
