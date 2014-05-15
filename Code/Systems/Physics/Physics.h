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
// Forwards
//
//=============================================================================

interface IContext;
interface IContextNotify;
interface IColliderComponent;
interface IRigidBodyComponent;



//=============================================================================
//
// Constants
//
//=============================================================================

enum class EMaterial
{
    Solid,
    Liquid
};



//=============================================================================
//
// IContext
//
//=============================================================================

interface IContext
{
    virtual void Initialize () pure;
    virtual void Uninitialize () pure;
    virtual void Update (Time::Delta deltaTime) pure;

    virtual void NotifyRegister (IContextNotify * notify) pure;
    virtual void NotifyUnregister (IContextNotify * notify) pure;

    virtual void SetGravity (const Vector2 & gravity) pure;
    virtual Vector2 GetGravity () const pure;

    virtual void DebugToggleRigidBody() pure;
    virtual void DebugToggleCollider() pure;
};

IContext * GetContext ();



//=============================================================================
//
// IContextNotify
//
//=============================================================================

interface IContextNotify : TNotifyTarget<IContextNotify>
{
    virtual void OnPhysicsPreTick () {};
    virtual void OnPhysicsPostTick () {};
};



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

    virtual void SetMass (float32 mass) pure;
    virtual float32 GetMass () const pure;

    virtual void AddForce (const Vector2 & f, const Point2 & at) pure;
    virtual void AddForce (const Vector2 & f) pure;
    virtual void AddTorque (float32 t) pure;
};



//=============================================================================
//
// IColliderComponent
//
//=============================================================================

interface IColliderComponent : IComponent
{
    static const ComponentType TYPE;
    static IColliderComponent * Attach (IEntity * entity, const Circle & circle, EMaterial material = EMaterial::Solid);
    static IColliderComponent * Attach (IEntity * entity, const Aabb2 & aabb, EMaterial material = EMaterial::Solid);

    virtual void SetGroups(Flags32 groupMasks) pure;

    virtual EMaterial GetMaterial () const pure;

    virtual Polygon2 GetPolygon () const pure;
};

} // namespace Physics