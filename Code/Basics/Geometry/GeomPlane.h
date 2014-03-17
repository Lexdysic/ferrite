//==================================================================================================
//
// File:    GeomPlane.h
// Author:  Jason Jackson
// Date:    December 5th, 2008
//
// A plane represented in the ax + by + cz + d = 0 implicit form
//
//=================================================================================================

#ifdef GEOMPLANE_H
#  error "Cannot include header more than once."
#endif
#define GEOMPLANE_H

//=============================================================================
//
// Represents a plane in 2-space by the ax + by + d = 0 implicit form
//
//=============================================================================
class Plane2
{
public:
    Plane2();
    Plane2( const p2 & point, const v2 & normal );
    Plane2( const p2 & a, const p2 & b );
    Plane2( float32 a, float32 b, float32 d );

    static const Plane2 X;
    static const Plane2 Y;

    union 
    {
        struct { v2 n; float32 d; };
        struct { float32 a, b, d; };                //!< Coefficients of the implicit equation
    };
};

//=============================================================================
//
// Represents a plane in 3-space by the ax + by + cz + d = 0 implicit form
//
//=============================================================================
class Plane3
{
public:
    Plane3();
    Plane3( const p3 & point, const v3 & normal );
    Plane3( const p3 & a, const p3 & b, const p3 & c );
    Plane3( float32 a, float32 b, float32 c, float32 d );

    static const Plane3 YZ;
    static const Plane3 XZ;
    static const Plane3 XY;

    union 
    {
        struct { v3 n; float32 d; };
        struct { float32 a, b, c, d; };             //!< Coefficients of the implicit equation
    };
};