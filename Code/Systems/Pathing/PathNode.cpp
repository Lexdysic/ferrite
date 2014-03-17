#include "PathPch.h"

namespace Pathing
{

//=============================================================================
CNode::CNode (IData * data) :
    m_data(data)
{
}

//=============================================================================
CNode::~CNode ()
{
    delete m_data;
}

//=============================================================================
void * CNode::operator new (size_t)
{
    return CContext::Get()->GetNodeAllocator().New();
}

//=============================================================================
void CNode::operator delete (void * ptr)
{
    CContext::Get()->GetNodeAllocator().Delete(ptr);
}

//=============================================================================
void CNode::AddNeighbor (CNode * node)
{
    m_neighbors.Add(node);
}

//=============================================================================
TArray<INode *> CNode::GetNeighbors ()
{
    TArray<INode *> outNodes;
    outNodes.Reserve(m_neighbors.Count());

    for (CNode * node : m_neighbors)
        outNodes.Add(node);

    return outNodes;
}

} // namespace Pathing