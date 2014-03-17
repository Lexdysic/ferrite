//==================================================================================================
//
// File:    GeomLozenge.h
// Author:  Jason Jackson
// Date:    December 5th, 2008
//
// A lozenge represents a sphere swept rectangle in space
//
//=================================================================================================

#ifdef GEOMLOZENGE_H
#  error "Cannot include header more than once."
#endif
#define GEOMLOZENGE_H

//=============================================================================
//
// A lozenge in 3-space
//
//=============================================================================
class Lozenge3
{
public:
    Lozenge3();
    Lozenge3( const p3 & center, const v3 & u, const v3 & v, float32 radius );

    p3  center;
    union
    {
        struct{ v3 extent[2]; };
        struct{ v3 u, v; };
    };
    float32 radius;
};