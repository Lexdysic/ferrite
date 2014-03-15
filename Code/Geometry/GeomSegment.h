//==================================================================================================
//
// File:    GeomSegment.h
// Author:  Jason Jackson
// Date:    December 5th, 2008
//
// A finite line represented by its two end points
//
//=================================================================================================

#ifdef GEOMSEGMENT_H
#  error "Cannot include header more than once."
#endif
#define GEOMSEGMENT_H

//=============================================================================
//
// Segment2
//
//=============================================================================

class Segment2
{
public:
    Segment2 ();
    Segment2 (const Point2 & a, const Point2 & b);

    Point2 a;
    Point2 b;
};

//=============================================================================
//
// Segment3
//
//=============================================================================

class Segment3
{
public:
    Segment3 ();
    Segment3 (const Point3 & a, const Point3 & b);

    Point3 a;
    Point3 b;
};
