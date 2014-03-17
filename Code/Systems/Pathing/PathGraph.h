namespace Pathing
{

class CGraph :
    public IGraph
{
public:

    CGraph ();
    ~CGraph ();

public:

    static CGraph * From (IGraph * graph) { return (CGraph *)graph; }
    static const CGraph * From (const IGraph * graph) { return (CGraph *)graph; }

public: // Intrusive links

    TLink<CGraph> m_link;

public:

    INode * NodeAdd (IData * data) override;

    void EdgeAddDirected (INode * start, INode * end) override;
    void EdgeAddSymetric (INode * a, INode * b) override;

    TArray<INode *> GetNodes () override;
private:

    TArray<CNode *> m_nodes;

};



} // namespace Pathing