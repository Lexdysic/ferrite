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
    typedef LIST_DECLARE(CRigidBodyComponent, m_link) RigidBodyList;
    typedef LIST_DECLARE(CColliderComponent, m_link) ColliderList;

    // Data
    RigidBodyList m_rigidBodyList;
    ColliderList  m_colliderList;
    Time::Point   m_time;
    Time::Delta   m_timeAccumulator;
    Vector2       m_gravity;

    // Debug
    bool m_debugDrawRigidBody;
    bool m_debugDrawColliders;

    // Helpers
    void Tick ();
    void Cleanup ();
};

} // namespace Physics