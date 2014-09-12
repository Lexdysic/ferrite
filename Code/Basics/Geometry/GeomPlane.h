#ifdef GEOMPLANE_H
#  error "Cannot include header more than once."
#endif
#define GEOMPLANE_H


//*****************************************************************************
//
// Plane2
//
//*****************************************************************************

class Plane2
{
public:
    Plane2 ();
    Plane2 (const Point2 & point, const Vector2 & normal);
    Plane2 (const Point2 & a, const Point2 & b);
    Plane2 (float32 a, float32 b, float32 d);

    static const Plane2 X;
    static const Plane2 Y;

    union 
    {
        struct { Vector2 n; float32 d; };
        struct { float32 a, b, d; };                //!< Coefficients of the implicit equation
    };
};



//*****************************************************************************
//
// Plane3
//
//*****************************************************************************
class Plane3
{
public:
    Plane3 ();
    Plane3 (const Point3 & point, const Vector3 & normal);
    Plane3 (const Point3 & a, const Point3 & b, const Point3 & c);
    Plane3 (float32 a, float32 b, float32 c, float32 d);

    static const Plane3 YZ;
    static const Plane3 XZ;
    static const Plane3 XY;

    union 
    {
        struct { Vector3 n; float32 d; };
        struct { float32 a, b, c, d; };             //!< Coefficients of the implicit equation
    };
};