namespace Physics
{

class CContext :
    public IContext,
    private Graphics::CContextNotify
{
public:
    CContext ();
    ~CContext ();
    
    void OnCreate (CRigidBodyComponent * comp);
    void OnCreate (CColliderComponent * comp);
    void OnDestroy (CColliderComponent * comp);

public: // Static -------------------------------------------------------------

    static CContext * Get () { return &s_context; }
    static CContext s_context;

public: // IContext -----------------------------------------------------------

    void Initialize () override;
    void Uninitialize () override;
    void Update (Time::Delta deltaTime) override;

    void SetGravity (const Vector2 & gravity) override { m_gravity = gravity; }
    Vector2 GetGravity () const override { return m_gravity; }

    void DebugToggleRigidBody() override;
    void DebugToggleCollider() override;

private: // Graphics::CContextNotify ------------------------------------------

    void OnGraphicsDebugRender (Graphics::IRenderTarget * renderTarget) override;

private:
    // Types
    typedef LIST_DECLARE(CRigidBodyComponent, m_linkAll)     RigidBodyList;
    typedef LIST_DECLARE(CColliderComponent, m_linkAll)      ColliderAllList;
    typedef LIST_DECLARE(CColliderComponent, m_linkMaterial) ColliderMaterialList;

    // Data
    RigidBodyList           m_rigidBodyList;
    ColliderAllList         m_colliderList;
    ColliderMaterialList    m_solidList;
    ColliderMaterialList    m_liquidList;
    Time::Delta             m_timeAccumulator;
    Vector2                 m_gravity;
    CBroadphase             m_broadphase;

    // Debug
    bool m_debugDrawRigidBody;
    bool m_debugDrawColliders;
    uint m_debugCollisionCount;

    // Helpers
    void Tick ();
    void Detection ();
    void Integrate ();
    void Response (CColliderComponent * colliderA, CColliderComponent * colliderB);
    void Cleanup ();
};

} // namespace Physics