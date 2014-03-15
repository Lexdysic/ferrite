//==================================================================================================
//
// File:    GeomSlab.h
// Author:  Jason Jackson
// Date:    December 5th, 2008
//
// A thick plane represented in the same way that a Plane is represeted. Instead the d-component
// is an interval
//
//=================================================================================================

#ifdef GEOMSLAB_H
#  error "Cannot include header more than once."
#endif
#define GEOMSLAB_H

//=============================================================================
//
// Slab3
//
//=============================================================================
class Slab3
{
public:
    Slab3();
    
    union
    {
        struct { v3 normal; float32 dNear; float32 dFar; };
        struct { v3 n; Interval extents; };
    };
};