namespace Pathing
{

class CNode;

typedef TArray<CNode *> NodeArray;

class CNode :
    public INode
{
public: // Public

    CNode (IData * data);
    ~CNode ();

    void AddNeighbor (CNode * node);

    inline const NodeArray & Neighbors () const { return m_neighbors; }

    void * operator new (size_t);
    void operator delete (void * ptr);

public: // Static

    static CNode * From (INode * x) { return (CNode *)x; }
    static const CNode * From (const INode * x) { return (CNode *)x; }

public: // INode

    IData * GetData () const override { return m_data; }

    TArray<INode *> GetNeighbors () override;

private: // Data

    TArray<CNode *> m_neighbors;
    IData *         m_data;

};

typedef TBlockAllocator<CNode, 32> CNodeAllocator;

} // namespace Pathing