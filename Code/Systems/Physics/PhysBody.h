//=================================================================================================
//
// File:    PhysBody.h
// Author:  Jason Jackson
// Date:    June 27, 2009
//
// Represents the phsysical properties of a body moving in space
//
//=================================================================================================

#ifdef PHYSBODY_H
#  error "Cannot include header more than once."
#endif
#define PHYSBODY_H

namespace Physics {

struct Body2 {
    Point2  linearPosition;
    Vector2 linearVelocity;

    Radian  angularPosition;
    Radian  angularVelocity;

    float32 invMass;
    float32 invMomentOfInertia; //!< Equivelent to mass for rotations

    float32 coeffOfRestitution;
};


struct Body3 {
    Point3   linearPosition;
    Vector3  linearVelocity;

    Matrix33 orienation;
    Vector3  angularVelocity;
    Vector3  angularMomentum;


    float32  invMass;
    Matrix33 invInertiaTensor;   //!< Equivelent to mass for rotations

    float32  coeffOfRestitution;
};

} // namespace Physics