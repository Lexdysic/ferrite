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
    void Tick ();

public: // Static -------------------------------------------------------------

    static CContext * Get () { return &s_context; }
    static CContext s_context;

public: // IContext -----------------------------------------------------------

    void Initialize () override;
    void Uninitialize () override;
    void Update (Time::Delta deltaTime) override;

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

    // Debug
    bool m_debugDrawRigidBody;
    bool m_debugDrawColliders;
};

} // namespace Physics