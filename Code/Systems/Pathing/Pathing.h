#ifdef PATHING_H
#   error "Cannot include header more than once"
#endif
#define PATHING_H

namespace Pathing
{

interface IContext;
interface IContextNotify;
interface IGraph;
interface IQuery;
interface INode;
interface IData;



//==================================================================================================
//
// Cost Functions
//
//==================================================================================================

typedef float (* FDistance)(INode * a, INode * b);
typedef float (* FHeuristic)(INode * a, INode * b);



//==================================================================================================
//
// CContextNotify
//
//==================================================================================================

struct CContextNotify : TNotifyTarget<CContextNotify>
{
    virtual void OnPathingQueryFinished (IQuery * query) {}
};



//==================================================================================================
//
// IContext
//
//==================================================================================================

interface IContext
{
    virtual void     Update () pure;

    // Graph
    virtual IGraph * GraphCreate () pure;
    virtual void     GraphDestroy (IGraph * graph) pure;

    // Query
    virtual IQuery * QueryCreate (
        IGraph *   graph,
        INode *    start,
        INode *    goal,
        FDistance  distance,
        FHeuristic heuristic
    ) pure;
    virtual void     QueryDestroy (IQuery * query) pure;

    // Notify
    virtual void NotifyAdd (CContextNotify * target) pure;
    virtual void NotifyRemove (CContextNotify * target) pure;

    // Debug
    virtual uint DebugUpdateCount () const pure;
};

IContext * GetContext();



//==================================================================================================
//
// IGraph
//
//==================================================================================================
interface IGraph
{
    virtual INode * NodeAdd (IData * data) pure;

    virtual void EdgeAddDirected (INode * start, INode * end) pure;
    virtual void EdgeAddSymetric (INode * a, INode * b) pure;

    virtual TArray<INode *> GetNodes () pure;
};



//==================================================================================================
//
// IQuery
//
//==================================================================================================
interface IQuery
{
    virtual INode * GetStart () const pure;
    virtual INode * GetEnd () const pure;

    virtual bool IsFinished () const pure;

    virtual TArray<INode *> GetPath () const pure;
};



//==================================================================================================
//
// INode
//
//==================================================================================================
interface INode
{
    virtual IData * GetData () const pure;
    
    template <typename T>
    T * GetData () const { return (T *)GetData(); }

    virtual TArray<INode *> GetNeighbors () pure;
};



//==================================================================================================
//
// IData
//
//==================================================================================================
interface IData
{
    // Intentionally blank
};





} // namespace Pathing