namespace Pathing
{



//=============================================================================
//
// Proxy
//
//============================================================================

struct Proxy
{
    explicit Proxy (CNode * node);

    enum class ELocation
    {
        None,
        Closed,
        Open
    };

    CNode *         graphNode;
    ELocation       location;
    float           score;      // G
    float           heuristic;  // H
    float           total;      // F = G + H
    const Proxy *   previous;

    bool operator== (const CNode * rhs) const { return graphNode == rhs; }
    bool operator< (const Proxy & rhs) const { return total > rhs.total; }

    void * operator new (size_t);
    void operator delete (void * ptr);
};

typedef TBlockAllocator<Proxy, 64> CProxyAllocator;



//=============================================================================
//
// CQuery
//
//============================================================================

class CQuery :
    public IQuery
{
    CLASS_CONVERSION(CQuery, IQuery);

public: // Internal ----------------------------------------------------------

    CQuery (
        CNode *         start,
        CNode *         goal,
        FHeuristic      heuristic,
        FDistance       distance
    );
    ~CQuery ();

    void Update ();

public: // IQuery ------------------------------------------------------------

    INode * GetStart () const override { return m_start; }
    INode * GetEnd () const override { return m_goal; }

    bool IsFinished () const override { return m_state != EState::Working; }

    TArray<INode *> GetPath () const override;

public: // Links --------------------------------------------------------------

    TLink<CQuery> m_link;

private: // -------------------------------------------------------------------

    typedef TDictionary<const CNode *, Proxy *> MapNodeToProxy;
    typedef TSet<Proxy *>                       ProxySet;
    typedef TPriQueue<Proxy *>                  ProxyQueue;
    typedef TArray<Proxy *>                     ProxyArray;

    enum class EState
    {
        Working,
        Failed,
        Success
    };

    // Data
    EState          m_state;
    CGraph          m_graph;
    MapNodeToProxy  m_lookup;
    ProxyQueue      m_open;
    CNode *         m_start;
    CNode *         m_goal;
    FHeuristic      m_heuristic;
    FDistance       m_distance;

    // Helpers
    Proxy *       GetProxy (CNode * node);
    const Proxy * GetProxy (CNode * node) const;
    void          PutInOpen (Proxy * proxy);
    void          PutInClosed (Proxy * proxy);
    void          Finalize (EState state);
};



} // namespace Pathing