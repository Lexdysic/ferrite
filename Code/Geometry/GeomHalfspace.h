//==================================================================================================
//
// File:    GeomHalfspace.cpp
// Author:  Jason Jackson
// Date:    December 5th, 2008
//
// Represents an object which consumes half of the current space
//
//=================================================================================================

#ifdef GEOMHALFSPACE_H
#  error "Cannot include header more than once."
#endif
#define GEOMHALFSPACE_H

//=============================================================================
//
// A 3-space halfspace
//
//=============================================================================
class Halfspace3
{
public:
    Halfspace3();
    Halfspace3( const p3 & point, const v3 & outwardNormal );
    
    p3 point;
    v3 normal;
};