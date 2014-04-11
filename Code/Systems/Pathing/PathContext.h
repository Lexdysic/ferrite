namespace Pathing
{

typedef TNotifier<CContextNotify> Notifier;

class CContext :
    public IContext
{
public: // Internal -----------------------------------------------------------

    CContext ();
    ~CContext ();

    CNodeAllocator & GetNodeAllocator () { return m_nodeAllocator; }
    CProxyAllocator & GetProxyAllocator () { return m_proxyAllocator; }
    Notifier & GetNotifier () { return m_notifier; }

public: // Static -------------------------------------------------------------

    static CContext * Get () { return &s_context; }
    static CContext s_context;

public: // IContext -----------------------------------------------------------

    void     Update () override;

    IGraph * GraphCreate () override;
    void     GraphDestroy (IGraph * graph) override;

    IQuery * QueryCreate (
        IGraph *   graph,
        INode *    start,
        INode *    goal,
        FDistance  distance,
        FHeuristic heuristic
    ) override;
    void     QueryDestroy (IQuery * query) override;

    // Notifications
    void NotifyAdd (CContextNotify * target) override;
    void NotifyRemove (CContextNotify * target) override;

    uint DebugUpdateCount () const override { return m_debugUpdateCount; }

private: // -------------------------------------------------------------------

    // Types
    typedef LIST_DECLARE(CGraph, m_link) GraphList;
    typedef LIST_DECLARE(CQuery, m_link) QueryList;

    // Data
    GraphList       m_graphs;
    QueryList       m_queries;
    QueryList       m_queriesFinished;
    CNodeAllocator  m_nodeAllocator;
    CProxyAllocator m_proxyAllocator;
    Notifier        m_notifier;

    // Debug
    uint            m_debugUpdateCount;
};

} // namespace Pathing