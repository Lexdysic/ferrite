#ifndef SYSTEMS_ENTITY_H
#define SYSTEMS_ENTITY_H

#include "Utilities/Notifier.h"
#include "Utilities/IdManager.h"
#include "Core/Token/Token.h"
#include "Core/Pointer/Pointer.h"


//=============================================================================
//
// Forward Declars
//
//=============================================================================

interface IContext;
interface IEntity;
interface IComponent;
class CComponent;
struct CEntityNotify;

typedef TId<IEntity> EntityId;
typedef TId<IComponent> ComponentId;
typedef Token ComponentType;



//=============================================================================
//
// IEntityContext
//
//=============================================================================

interface IEntityContext
{
    virtual IEntity * CreateEntity () pure;
    virtual void      DestroyEntity (IEntity * entity) pure;
    virtual IEntity * GetEntity (EntityId id) pure;

    virtual void Initialize () pure;
    virtual void Uninitialize () pure;
    virtual void Update () pure;

    virtual void NotifyRegister (CEntityNotify * target) pure;
    virtual void NotifyUnregister (CEntityNotify * target) pure;

    virtual void DebugToggleDraw () pure;
};

IEntityContext * EntityGetContext ();



//=============================================================================
//
// IEntity
//
//=============================================================================

interface IEntity : IRefCounted<IEntity>
{
    virtual EntityId GetId () const pure;

    virtual void Attach (CComponent * pComponent) pure;
    virtual void Detach (CComponent * pComponent) pure;

    template <typename T>
    T * Get () { return dynamic_cast<T *>(Get(T::TYPE)); } // TODO: rework to not need dynamic cast
    virtual CComponent * Get (const ComponentType & type) pure;

    virtual uint         GetComponentCount () const  pure;
    virtual CComponent * EnumComponent (uint i) pure;

    typedef TStrongPtr<IEntity> Ptr;
    typedef TWeakPtr<IEntity>   Ref;
};



//=============================================================================
//
// IComponent
//
//=============================================================================

interface IComponent
{
    virtual ComponentId     GetId () const pure;
    virtual IEntity *       GetOwner () const pure;
    virtual ComponentType   GetType () const pure;
};



//=============================================================================
//
// CComponent
//
//=============================================================================

class CComponent
{
    friend class CEntity;
public:
    CComponent ();
    virtual ~CComponent ();

public: // IComponent ---------------------------------------------------------

    ComponentId     GetId () const;
    IEntity *       GetOwner () const;
    virtual ComponentType   GetType () const;

protected: // Notifications ---------------------------------------------------

    virtual void OnAttached (IEntity * entity);
    virtual void OnDetached (IEntity * entity);

private: // -------------------------------------------------------------------

    void Attached (IEntity * entity);
    void Detached (IEntity * entity);

    ComponentId m_id;
    IEntity *   m_owner;
};



//=============================================================================
//
// CTransformComponent2
// TODO (jasonj): Move this to its own home
//
//=============================================================================

class CTransformComponent2 : 
    public CComponent,
    public IComponent
{
public:

    CTransformComponent2 ();
    ~CTransformComponent2 ();

public:

    static const ComponentType TYPE;
    static CTransformComponent2 * Attach (IEntity * entity);

public: // CComponent

    ComponentId   GetId () const override { return CComponent::GetId(); }
    IEntity *     GetOwner () const override{ return CComponent::GetOwner(); }
    ComponentType GetType () const override { return TYPE; }

public:

    void SetParent (CTransformComponent2 * parent);
    void SetParent (IEntity * entity);

    Point2 GetPosition () const;
    const Point2 & GetPositionLocal () const;
    void SetPosition (const Point2 & pos);
    void SetPositionLocal (const Point2 & pos);
    void UpdatePosition (const Vector2 & delta);
    void UpdatePositionLocal (const Vector2 & delta);

    Radian GetRotation () const;
    Radian GetRotationLocal () const;
    void SetRotation (Radian angle);
    void SetRotationLocal (Radian angle);
    void UpdateRotation (Radian delta);
    void UpdateRotationLocal (Radian delta);

    Matrix23 GetMatrix () const;

public: // Links

    LIST_LINK(CTransformComponent2) m_link;

private:

    CTransformComponent2 *  m_parent;
    Point2                  m_positionLocal;
    Radian                  m_rotationLocal;


};


//=============================================================================
//
// CEntityNotify
//
//=============================================================================

struct CEntityNotify : TNotifyTarget<CEntityNotify>
{
    virtual void OnEntityUpdate ();
};



//=============================================================================
//
// Helper Functions
//
//=============================================================================

//=============================================================================
// TODO: move to inl file?
template <typename T, typename... Ts>
T * EnsureComponent (IEntity * entity, const Ts &... Vs)
{
    if (T * comp = entity->Get<T>())
        return comp;

    return T::Attach(entity, Vs...);
}

#endif // SYSTEMS_ENTITY_H