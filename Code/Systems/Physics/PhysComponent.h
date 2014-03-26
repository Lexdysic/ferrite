

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
    friend class CContext;
public:

    CRigidBodyComponent ();
    ~CRigidBodyComponent ();

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

    void AddForce (const Vector2 & f, const Point2 & at) override;
    void AddForce (const Vector2 & f) override;
    void AddTorque (float32 t) override;

public: // Links

    LIST_LINK(CRigidBodyComponent) m_link;

private:

    // Data
    Vector2 m_linearVelocity;
    Radian  m_angularVelocity;
    Vector2 m_force;
    float32 m_torque;

    float32 m_mass;
    float32 m_momentOfInertia;
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
    enum class EType;

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
    Polygon2 GetPolygon () const override;

public: // Links

    LIST_LINK(CColliderComponent) m_link;

private:

    enum class EType
    {
        Circle,
        Box,
    };


    EType m_type;
    Circle m_circle;
    Aabb2  m_aabb;

    float32     m_coeffOfRestitution;
    Flags32     m_groupMask;

};

} // Physics