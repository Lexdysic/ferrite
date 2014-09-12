#ifdef GEOMTRIANGLE_H
#  error "Cannot include header more than once."
#endif
#define GEOMTRIANGLE_H

//*****************************************************************************
//
// Triangle2
//
//*****************************************************************************

class Triangle2
{
public: // Construction

    Triangle2 () = default;
    Triangle2 (const Point2 & a, const Point2 & b, const Point2 & c);

public: //

    Geometry::EWinding ComputeWiding () const;
    float32 ComputeArea () const;
    Point2 ComputeCentroid () const;

public: // Data

    union 
    {
        struct { Point2 p[3]; };
        struct { Point2 a, b, c; };
    };
};



//*****************************************************************************
//
// Triangle3
//
//*****************************************************************************

class Triangle3
{
public: // Construction

    Triangle3 () = default;
    Triangle3 (const Point3 & a, const Point3 & b, const Point3 & c);

public: // Data

    union 
    {
        struct { Point3 p[3]; };
        struct { Point3 a, b, c; };
    };
};
