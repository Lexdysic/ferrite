//==================================================================================================
//
// File:    GeomRay.h
// Author:  Jason Jackson
// Date:    December 5th, 2008
//
// A line which starts a point in space and extends infinitely in one direction
//
//=================================================================================================

#ifdef GEOMRAY_H
#  error "Cannot include header more than once."
#endif
#define GEOMRAY_H
//=============================================================================
//
// Represents a ray with a starting point a direction vector
//
//=============================================================================
class Ray2
{
public:
    Ray2();
    Ray2( const p2 & origin, const v2 & direction );

    p2 origin;      //!< The start point of the ray
    v2 direction;   //!< The vector direction of the ray (need not be normalized)
};

//=============================================================================
//
// Represents a ray with a starting point a direction vector
//
//=============================================================================
class Ray3
{
public:
    Ray3();
    Ray3( const p3 & origin, const v3 & direction );

    p3 origin;      //!< The start point of the ray
    v3 direction;   //!< The vector direction of the ray (need not be normalized)
};
