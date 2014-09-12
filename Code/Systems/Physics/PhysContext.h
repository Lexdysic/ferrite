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

    void NotifyRegister (IContextNotify * notify) override;
    void NotifyUnregister (IContextNotify * notify) override;

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
    typedef TNotifier<IContextNotify>                        CNotify;

    struct Contact
    {
        Point2 point;
        Vector2 normal;
    };

    struct Manifold
    {
        Contact contacts[2];
    };

    struct CollisionResult
    {
        float32 separation;
        Vector2 direction;
        bool    isCollide;
        bool    willCollide;
    };

    // Data
    CNotify                 m_notifier;
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
    bool CheckCollision (
        const Polygon2 & polygonA,
        const Polygon2 & polygonB,
        const Vector2 & relativeVelocity,
        CollisionResult * result
    ) const;
    
    bool CheckCollisionSingle (
        const Polygon2 & polygonCheck,
        const Polygon2 & polygonA,
        const Polygon2 & polygonB,
        const Vector2 & relativeVelocity,
        CollisionResult * result
    ) const;
    void Response (
        CColliderComponent * colliderA,
        CColliderComponent * colliderB,
        const CollisionResult & result
    );
    void Cleanup ();
};

} // namespace Physics