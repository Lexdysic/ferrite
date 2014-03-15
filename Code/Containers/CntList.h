/******************************************************************************
*
*   List.h
*   
*
*   By Patrick Wyatt - 5/16/2010
*
***/


/******************************************************************************
*
*   WHAT IT IS
*
*   This module defines a linked-list implementation that uses "embedded"
*   links rather than separately allocated link-nodes as does STL and
*   more or less all other linked-list implementations.
*
*   Why is this cool:
*       1. No additional memory allocations (malloc) required to link
*           an object into a linked list.
*       2. Not necessary to traverse an additional pointer references
*           to get to the object being dereferenced.
*       3. Probably most importantly, when objects get deleted, they
*           automatically unlink themselves from the lists they're
*           linked to, eliminating many common types of bugs.
*
*   HOW TO USE IT
*
*   Declare a structure that will be contained in one or more linked lists:
*       class CFoo {
*           LIST_LINK(CFoo) m_linkByData;
*           LIST_LINK(CFoo) m_linkByType;
*           int             m_data;
*           int             m_type;
*           ...
*       };
*
*   Declare list variables:
*       LIST_DECLARE(CFoo, m_linkByData) listByData;
*       LIST_DECLARE(CFoo, m_linkByType) listByType;
*       LIST_PTR(CFoo) m_listPtr = foo ? &listByData : &listByType;
*
*   Operations on links:
*       T * Prev ();
*       T * Next ();
*       void Unlink ();
*       bool IsLinked () const;
*
*   Operations on lists:
*       bool Empty () const;
*       void UnlinkAll ();
*       void DeleteAll ();
*
*       T * Head (); 
*       T * Tail ();
*       T * Prev (T * node);
*       T * Next (T * node);
*
*       void InsertHead (T * node);
*       void InsertTail (T * node);
*       void InsertBefore (T * node, T * before);
*       void InsertAfter (T * node, T * after);
*
*   NOTES
*
*   Limitations:
*       All nodes must be allocated on (at least) two-byte boundaries
*       because the low bit is used as a sentinel to signal end-of-list.
*       
*   Thanks to:
*       Something like this code was originally implemented by Mike
*       O'Brien in storm.dll for Diablo in 1995, and again at ArenaNet
*       for Guild Wars.
*
***/


/******************************************************************************
*
*   List definition macros
*
***/

// Define a linked list:
// T    = type of object being linked
// link = member within object which is the link field
#define LIST_DECLARE(T, link) TListDeclare<T, offsetof(T, link)>

// Define a field within a structure that will be used to link it into a list
#define LIST_LINK(T) TLink<T>

// Define a pointer to a list
#define LIST_PTR(T) TList<T> *


template <typename T>
class TList;

//=============================================================================
//
//  TLink<T>
//
//=============================================================================

template<class T>
class TLink
{
public:

    ~TLink ();
    TLink ();

    bool IsLinked () const;
    void Unlink ();

    T * Prev ();
    T * Next ();
    const T * Prev () const;
    const T * Next () const;

public:

    // For use by list-type classes, not user code;
    // the alternative is to friend TList<T>, THash<T>,
    // and (eventually) many other structures.
    TLink (size_t offset);
    void SetOffset (size_t offset);
    TLink<T> * NextLink ();
    TLink<T> * PrevLink ();
    void InsertBefore (T * node, TLink<T> * nextLink);
    void InsertAfter (T * node, TLink<T> * prevLink);

private:

    T *         m_nextNode; // pointer to the next >object<
    TLink<T> *  m_prevLink; // pointer to the previous >link field<
    void RemoveFromList ();

    CLASS_NO_COPY(TLink);
};


//=============================================================================
//
//  TList<T>
//
//=============================================================================

template<class T>
class TList {
public:
    ~TList ();
    TList ();

    bool IsEmpty () const;
    void UnlinkAll ();
    void DeleteAll ();

    T * Head (); 
    T * Tail ();
    const T * Head () const;
    const T * Tail () const;

    T * Prev (T * node);
    T * Next (T * node);
    const T * Prev (const T * node) const;
    const T * Next (const T * node) const;

    void InsertHead (T * node);
    void InsertTail (T * node);
    void InsertBefore (T * node, T * before);
    void InsertAfter (T * node, T * after);

private:
    TLink<T>    m_link;
    size_t      m_offset;

    TList (size_t offset);
    TLink<T> * GetLinkFromNode (const T * node) const;

    template<class T, size_t offset>
    friend class TListDeclare;

    CLASS_NO_COPY(TList<T>);
};


//=============================================================================
//
//  TListDeclare<T, offset>
//
//=============================================================================

template <class T, size_t offset>
class TListDeclare : public TList<T> {
public:
    TListDeclare ();
};


//=============================================================================
//
//  TListIterator<T>
//
//=============================================================================

template <class T>
class TListIterator :
    std::iterator<
        std::bidirectional_iterator_tag,
        T,
        void
    >
{
public:
    TListIterator ();
    TListIterator (T * curr, TList<T> * list);
    TListIterator (const TListIterator<T> & rhs);
    TListIterator<T> & operator= (const TListIterator<T> & rhs);

    bool operator == (const TListIterator<T> & rhs);
    bool operator != (const TListIterator<T> & rhs);

    TListIterator<T> & operator++ ();
    TListIterator<T> & operator++ (int);
    TListIterator<T> & operator-- ();
    TListIterator<T> & operator-- (int);

    T * operator* ();
    T * operator-> ();

private:
    T *         m_curr;
    TList<T> *  m_list;
};

template <typename T, size_t offset>
inline TListIterator<T> begin (TListDeclare<T, offset> & list);

template <typename T, size_t offset>
inline TListIterator<T> end (TListDeclare<T, offset> & list);