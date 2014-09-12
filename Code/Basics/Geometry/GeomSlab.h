#ifdef GEOMSLAB_H
#  error "Cannot include header more than once."
#endif
#define GEOMSLAB_H

//*****************************************************************************
//
// Slab3
//
//*****************************************************************************

class Slab3
{
public: // Construction

    Slab3 ();
    
public: // Data

    union
    {
        struct { Vector3 normal; float32 dNear; float32 dFar; };
        struct { Vector3 n; Interval extents; };
    };
};