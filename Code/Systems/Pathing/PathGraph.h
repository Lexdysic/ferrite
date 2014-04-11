namespace Pathing
{

class CGraph :
    public IGraph
{
    CLASS_CONVERSION(CGraph, IGraph);

public: // Internal -----------------------------------------------------------

    CGraph ();
    ~CGraph ();

public: // Links --------------------------------------------------------------

    TLink<CGraph> m_link;

public: // IGraph -------------------------------------------------------------

    INode * NodeAdd (IData * data) override;

    void EdgeAddDirected (INode * start, INode * end) override;
    void EdgeAddSymetric (INode * a, INode * b) override;

    TArray<INode *> GetNodes () override;

private: // Data --------------------------------------------------------------

    NodeArray m_nodes;

};



} // namespace Pathing