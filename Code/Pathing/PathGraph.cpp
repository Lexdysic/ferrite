#include "PathPch.h"

namespace Pathing
{

//=============================================================================
CGraph::CGraph ()
{
}

//=============================================================================
CGraph::~CGraph ()
{
    for (CNode * node : m_nodes)
        delete node;
}

//=============================================================================
INode * CGraph::NodeAdd (IData * data)
{
    CNode * node = new CNode(data);
    m_nodes.Add(node);
    return node;
}

//=============================================================================
void CGraph::EdgeAddDirected (INode * start, INode * end)
{
    CNode * nodeStart = CNode::From(start);
    CNode * nodeEnd = CNode::From(end);

    nodeStart->AddNeighbor(nodeEnd);
}

//=============================================================================
void CGraph::EdgeAddSymetric (INode * a, INode * b)
{
    CNode * nodeA = CNode::From(a);
    CNode * nodeB = CNode::From(b);

    nodeA->AddNeighbor(nodeB);
    nodeB->AddNeighbor(nodeA);
}

//=============================================================================
TArray<INode *> CGraph::GetNodes ()
{
    TArray<INode *> outNodes;
    outNodes.Reserve(m_nodes.Count());

    for (CNode * node : m_nodes)
        outNodes.Add(node);

    return outNodes;
}

} // namespace Pathing