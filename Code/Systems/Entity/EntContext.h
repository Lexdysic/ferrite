



//=============================================================================
//
// CContext
//
//=============================================================================

class CContext :
    public IEntityContext,
    Graphics::CContextNotify
{
public: // Internal -----------------------------------------------------------

    CContext ();
    ~CContext ();

    EntityIdManager & GetEntityIdManager () { return m_entityIdManager; }
    ComponentIdManager & GetComponentIdManager () { return m_componentIdManager; }

    void OnCreate (CTransformComponent2 * comp);
    void OnDestroy (CEntity * entity);

public: // Context ------------------------------------------------------------

    static CContext * Get () { return &s_context; };

    static CContext s_context;

private: // External ----------------------------------------------------------

    IEntity * CreateEntity () override;
    void      DestroyEntity (IEntity * entity) override;
    IEntity * GetEntity (EntityId id) override;

    void Initialize () override;
    void Uninitialize () override;
    void Update () override;

    void NotifyRegister (CEntityNotify * target) override;
    void NotifyUnregister (CEntityNotify * target) override;

    void DebugToggleDraw() override { m_debugDraw = !m_debugDraw; }

private: // Graphics::CContextNotify ------------------------------------------

    void OnGraphicsDebugRender (Graphics::IRenderTarget * renderTarget) override;

private: // -------------------------------------------------------------------

    typedef TNotifier<CEntityNotify> CNotifier;
    typedef TDictionary<EntityId, CEntity *> EntityMap;
    typedef LIST_DECLARE(CTransformComponent2, m_link) ListComponent;

    // Data
    EntityIdManager     m_entityIdManager;
    ComponentIdManager  m_componentIdManager;
    EntityMap           m_entities;
    CNotifier           m_notifier;
    ListComponent       m_transforms;

    // Debug
    bool m_debugDraw;
};
