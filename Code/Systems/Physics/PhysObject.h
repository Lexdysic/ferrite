//=================================================================================================
//
// File:    PhysObject.h
// Author:  Jason Jackson
// Date:    July 2, 2009
//
// Represents the geometric shape and physical properties of an object
//
//=================================================================================================

#ifdef PHYSOBJECT_H
#  error "Cannot include header more than once."
#endif
#define PHYSOBJECT_H

namespace Physics {

class Object2 {
    Body2   mBody;
    Sphere2 mGeom; // TODO: need an abstract geometry representation
};

class Object3 {
    Body3   mBody;
    Sphere3 mGeom; // TODO: need an abstract geometry representation
};

} // namespace Physics