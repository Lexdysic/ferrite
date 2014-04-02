#include "PathPch.h"

namespace Pathing
{



//=============================================================================
//
// Proxy
//
//============================================================================

//=============================================================================
void * Proxy::operator new (size_t)
{
    return CContext::Get()->GetProxyAllocator().Alloc();
}

//=============================================================================
void Proxy::operator delete (void * ptr)
{
    CContext::Get()->GetProxyAllocator().Free(ptr);
}



//=============================================================================
//
// CQuery
//
//============================================================================

//=============================================================================
CQuery::CQuery (
    CNode *         start,
    CNode *         goal,
    FHeuristic      heuristic,
    FDistance       distance
) :
    m_state(STATE_Working),
    m_start(start),
    m_goal(goal),
    m_heuristic(heuristic),
    m_distance(distance)
{
    Proxy * proxy = GetProxy(start);
    proxy->total = proxy->score + proxy->heuristic;
    PutInOpen(proxy);
}

//=============================================================================
CQuery::~CQuery ()
{
    for (auto it : m_lookup)
        delete it.second;
}

//=============================================================================
void CQuery::Update ()
{
    if (IsFinished())
        return;

    if (m_open.IsEmpty())
        return Finalize(STATE_Failed);

    Proxy * current = m_open.Pop();
    if  (current->graphNode == m_goal)
        return Finalize(STATE_Success);

    PutInClosed(current);

    for (CNode * neighborNode : current->graphNode->Neighbors())
    {
        Proxy * neighborProxy = GetProxy(neighborNode);

        if (neighborProxy->location == Proxy::LOCATION_Closed)
            continue;

        const float tentativeScore = current->score + m_distance(current->graphNode, neighborNode);

        // First time encountering this node
        if (neighborProxy->location != Proxy::LOCATION_Open)
        {
            neighborProxy->previous   = current;
            neighborProxy->score      = tentativeScore;
            neighborProxy->total      = neighborProxy->score + neighborProxy->heuristic;
            PutInOpen(neighborProxy);
        }
        // The path to this node is better coming from the current node
        else if (tentativeScore < neighborProxy->score)
        {
            neighborProxy->previous   = current;
            neighborProxy->score      = tentativeScore;
            neighborProxy->total      = neighborProxy->score + neighborProxy->heuristic;
            m_open.Resort();
        }
    }
}

//=============================================================================
Proxy * CQuery::GetProxy (CNode * node)
{
    ASSERT(node);

    Proxy * proxy = m_lookup.Find(node);
    if (!proxy)
    {
        proxy = new Proxy(node);
        proxy->heuristic = m_heuristic(node, m_goal);

        m_lookup.Set(node, proxy);
    }

    return proxy;
}

//=============================================================================
const Proxy * CQuery::GetProxy (CNode * node) const
{
    return m_lookup.Find(node);
}

//=============================================================================
void CQuery::PutInOpen (Proxy * proxy)
{
    proxy->location = Proxy::LOCATION_Open;
    m_open.Push(proxy);
}

//=============================================================================
void CQuery::PutInClosed (Proxy * proxy)
{
    proxy->location = Proxy::LOCATION_Closed;
}

//=============================================================================
TArray<INode *> CQuery::GetPath () const
{
    ASSERT(IsFinished());

    const Proxy * proxy = GetProxy(m_goal);

    const bool isInOpen = m_open.Contains(const_cast<Proxy * const>(proxy));
    if (isInOpen)
        return TArray<INode *>();

    TArray<INode *> outNodes;

    for ( ; proxy; proxy = proxy->previous)
        outNodes.Add(proxy->graphNode);

    std::reverse(outNodes.Ptr(), outNodes.Term());

    return outNodes;
}

//=============================================================================
void CQuery::Finalize (EState state)
{
    m_state = state;
    CContext::Get()->GetNotifier().Call(&CContextNotify::OnPathingQueryFinished, this);
}

} // namespace Pathing