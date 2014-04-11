#include "PathPch.h"

namespace Pathing
{


//==================================================================================================
//
// Constants
//
//==================================================================================================

const Time::Delta UPDATE_TIME_LIMIT = Time::Ms(2);



//==================================================================================================
//
// CContext
//
//==================================================================================================

//=============================================================================
CContext CContext::s_context;

//=============================================================================
CContext::CContext () :
    m_debugUpdateCount(0)
{
}

//=============================================================================
CContext::~CContext ()
{
    while (m_queries.Head())
        delete m_queries.Head();

    while (m_queriesFinished.Head())
        delete m_queriesFinished.Head();

    while (m_graphs.Head())
        delete m_graphs.Head();
}

//=============================================================================
void CContext::Update ()
{
    m_debugUpdateCount = 0;

    CRealTimer timer;
    do
    {
        for (CQuery * query = m_queries.Head(); query; query = m_queries.Next(query))
        {
            m_debugUpdateCount++;
            query->Update();

            if (query->IsFinished())
            {
                query->m_link.Unlink();
                m_queriesFinished.InsertBefore(query, null);
            }
        }
    }
    while (m_queries.Head() && timer.Elapsed() < UPDATE_TIME_LIMIT);
}

//=============================================================================
IGraph * CContext::GraphCreate ()
{
    CGraph * graph = new CGraph();
    m_graphs.InsertTail(graph);
    return graph;
}

//=============================================================================
void CContext::GraphDestroy (IGraph * g)
{
    CGraph * graph = CGraph::From(g);
    delete graph;
}

//=============================================================================
IQuery * CContext::QueryCreate (
        IGraph * graph,
        INode * start,
        INode * goal,
        FDistance distance,
        FHeuristic heuristic
) {
    ASSERT(graph);
    ASSERT(start);
    ASSERT(goal);
    ASSERT(distance);
    ASSERT(heuristic);

    CQuery * query = new CQuery(
        CNode::From(start),
        CNode::From(goal),
        heuristic,
        distance
    );
    m_queries.InsertTail(query);
    return query;
}

//=============================================================================
void CContext::QueryDestroy (IQuery * q)
{
    CQuery * query = CQuery::From(q);
    delete query;
}

//=============================================================================
void CContext::NotifyAdd (CContextNotify * target)
{
    m_notifier.Add(target);
}

//=============================================================================
void CContext::NotifyRemove (CContextNotify * target)
{
    m_notifier.Remove(target);
}


//==================================================================================================
//
// Functions
//
//==================================================================================================

//=============================================================================
IContext * GetContext()
{
    return CContext::Get();
}


} // namespace Pathing