//=================================================================================================
//
// File:    Phys.h
// Author:  Jason Jackson
// Date:    June 27, 2009
//
// Exported interface of the physics library
//
//=================================================================================================

#ifdef PHYS_H
#  error "Cannot include header more than once"
#endif
#define PHYS_H

namespace Physics
{

//=============================================================================
//
// Context
//
//=============================================================================

interface IContext
{
    virtual void Initialize () pure;
    virtual void Uninitialize () pure;
    virtual void Update (Time::Delta deltaTime) pure;

    virtual void DebugToggleRigidBody() pure;
    virtual void DebugToggleCollider() pure;
};

IContext * GetContext ();



//=============================================================================
//
// IRigidBodyComponent
//
//=============================================================================

interface IRigidBodyComponent : IComponent
{
    static const ComponentType TYPE;
    static IRigidBodyComponent * Attach (IEntity * entity);

    virtual const Vector2 & GetVelocity () const pure;
    virtual void SetVelocity (const Vector2 & v) pure;

    virtual Radian GetAngularVelocity () const pure;
    virtual void   SetAngularVelocity (Radian angle) pure;
};



//=============================================================================
//
// IColliderComponent
//
//=============================================================================

interface IColliderComponent : IComponent
{
    static const ComponentType TYPE;
    static IColliderComponent * Attach (IEntity * entity, const Circle & circle);
    static IColliderComponent * Attach (IEntity * entity, const Aabb2 & aabb);

    virtual void SetGroups(Flags32 groupMasks) pure;
};

} // namespace Physics