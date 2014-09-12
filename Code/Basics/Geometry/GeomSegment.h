#ifdef GEOMSEGMENT_H
#  error "Cannot include header more than once."
#endif
#define GEOMSEGMENT_H

//*****************************************************************************
//
// Segment2
//
//*****************************************************************************

class Segment2
{
public: // Construction

    Segment2 ();
    Segment2 (const Point2 & a, const Point2 & b);

public: // Data

    Point2 a;
    Point2 b;
};



//*****************************************************************************
//
// Segment3
//
//*****************************************************************************

class Segment3
{
public: // Construction

    Segment3 ();
    Segment3 (const Point3 & a, const Point3 & b);

public: // Data

    Point3 a;
    Point3 b;
};
