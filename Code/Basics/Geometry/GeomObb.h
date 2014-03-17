//==================================================================================================
//
// File:    GeomObb.h
// Author:  Jason Jackson
// Date:    December 5th, 2008
//
// An oriented bounding box which does not align to any native axis
//
//=================================================================================================

#ifdef GEOMOBB_H
#  error "Cannot include header more than once."
#endif
#define GEOMOBB_H

//=============================================================================
//
// Oriented bounding box, defined by a center and three mutually orthoganal 
// extent vectors (half-length
//
//=============================================================================
class Obb3
{
public:
    Obb3();
    Obb3( const p3 & center, const v3 & x, const v3 & y, const v3 & z );
    Obb3( const p3 & center, const v3 & unitX, const v3 & unitY, const v3 & unitZ, const v3 & extent );

    inline float32 ProjectedRadiusAlongVector( const v3 & v ) const;

    p3 center;      //!< Center of the box
    v3 extent;      //!< Positive halfwidth extents of Obb3 along each local axis
    v3 u[3];        //!< Local x-, y-, z-axes
};