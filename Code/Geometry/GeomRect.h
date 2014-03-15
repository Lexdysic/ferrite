//==================================================================================================
//
// File:    GeomRect.h
// Author:  Jason Jackson
// Date:    December 5th, 2008
//
// Represents a finite 2-d rectagular plane in 3-space
//
//=================================================================================================

#ifdef GEOMRECT_H
#  error "Cannot include header more than once."
#endif
#define GEOMRECT_H

//=============================================================================
//
// Rect3
//
//=============================================================================
class Rect3
{
public:
    Rect3 ();
    Rect3 (const Point3 & center, const Vector3 & x, const Vector3 & y);
    Rect3 (const Point3 & center, const Vector3 & unitX, const Vector3 & unitY, const Vector2 & extent);

    Point3 center;      //!< Center of the rectangle
    Vector3 u[2];       //!< Unit vectors for the local x-, and y-axes
    Vector2 extent;     //!< Local half-width of the rectangle
};
