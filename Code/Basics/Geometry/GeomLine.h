//==================================================================================================
//
// File:    GeomLine.h
// Author:  Jason Jackson
// Date:    December 5th, 2008
//
// A line extends infinitly  along a vector in both directions and passes through a point
//
//=================================================================================================

#ifdef GEOMLINE_H
#  error "Cannot include header more than once."
#endif
#define GEOMLINE_H

//=============================================================================
//
// Line2
//
//=============================================================================
class Line2
{
public:
    Line2 ();
    Line2 (const Point2 & a, const Point2 & b);
    Line2 (const Point2 & origin, const Vector2 & direction);


    Point2  origin;
    Vector2 direction;   // need not be normalized
};



//=============================================================================
//
// Line3
//
//=============================================================================
class Line3
{
public:
    Line3 ();
    Line3 (const Point3 & a, const Point3 & b);
    Line3 (const Point3 & origin, const Vector3 & direction);


    Point3  origin;
    Vector3 direction;   // need not be normalized
};