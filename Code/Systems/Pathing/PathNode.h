namespace Pathing
{

class CNode;

typedef TArray<CNode *> NodeArray;


class CNode :
    public INode
{
    CLASS_CONVERSION(CNode, INode);
public: // Internal -----------------------------------------------------------

    CNode (IData * data);
    ~CNode ();

    void AddNeighbor (CNode * node);

    inline const NodeArray & Neighbors () const { return m_neighbors; }

    void * operator new (size_t);
    void operator delete (void * ptr);

public: // INode --------------------------------------------------------------

    IData * GetData () const override { return m_data; }

    TArray<INode *> GetNeighbors () override;

private: // Data --------------------------------------------------------------

    NodeArray m_neighbors;
    IData *   m_data;

};

typedef TBlockAllocator<CNode, 32> CNodeAllocator;

} // namespace Pathing