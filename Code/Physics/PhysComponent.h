

namespace Physics
{

//=============================================================================
//
// CRigidBodyComponent
//
//=============================================================================

class CRigidBodyComponent :
    public IRigidBodyComponent,
    public CComponent
{
public:

    CRigidBodyComponent ();
    ~CRigidBodyComponent ();

    float32 mass;
    float32 invMass;
    float32 momentOfInertia;    // Equivelent to mass for rotations
    float32 invMomentOfInertia;

    void UpdateVelocity (const Vector2 & v);
    void UpdateAngularVelocity (Radian angle);

public: // IComponent

    ComponentId     GetId () const override { return CComponent::GetId(); }
    IEntity *       GetOwner () const override { return CComponent::GetOwner(); }
    ComponentType   GetType () const override { return IRigidBodyComponent::TYPE; }

private: // CComponent

    void OnAttached (IEntity * entity) override;

public: // IRigidBodyComponent

    const Vector2 & GetVelocity () const override { return m_linearVelocity; }
    void SetVelocity (const Vector2 & v) override { m_linearVelocity = v; }

    Radian GetAngularVelocity () const override { return m_angularVelocity; }
    void   SetAngularVelocity (Radian angle) override { m_angularVelocity = angle; }

public: // Links

    LIST_LINK(CRigidBodyComponent) m_link;

private:

    // Data
    Vector2 m_linearVelocity;
    Radian  m_angularVelocity;
};



//=============================================================================
//
// CColliderComponent
//
//=============================================================================

class CColliderComponent :
    public IColliderComponent,
    public CComponent
{
    enum EType
    {
        TYPE_CIRCLE,
        TYPE_BOX,
    };

public:

    CColliderComponent (const Circle & circle);
    CColliderComponent (const Aabb2 & aabb);
    CColliderComponent (EType type);
    ~CColliderComponent ();

    void RenderDebug(Graphics::IRenderTarget * renderTarget);


public: // IComponent

    ComponentId     GetId () const  override { return CComponent::GetId(); }
    IEntity *       GetOwner () const override { return CComponent::GetOwner(); }
    ComponentType   GetType () const override { return IColliderComponent::TYPE; }

private: // CComponent

    void OnAttached (IEntity * entity) override;

public: // IColliderComponent

    void SetGroups (Flags32 groupMask) override { m_groupMask = groupMask; }

public: // Links

    LIST_LINK(CColliderComponent) m_link;

private:

    EType m_type;
    Circle m_circle;
    Aabb2  m_aabb;

    float32     m_coeffOfRestitution;
    Flags32     m_groupMask;

};

} // Physics