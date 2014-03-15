//=================================================================================================
//
// File:    CoreTypelist.h
// Author:  Jason Jackson
// Date:    Semptember 1, 2009
//
// Definitions for type lists
//
//=================================================================================================

#ifdef CORETYPELIST_H
#  error "Cannot include header more than once"
#endif
#define CORETYPELIST_H


//=============================================================================
//
// Definition of a node link in a typelist 
//
//=============================================================================

template <typename T, typename U>
struct TypelistNode 
{
    typedef T Head;
    typedef U Tail;
};

struct NullType {};


//=============================================================================
//
// Defines a typelist
//
//=============================================================================

//=============================================================================
template <
    typename T01 = NullType, typename T02 = NullType, typename T03 = NullType, typename T04 = NullType, typename T05 = NullType, 
    typename T06 = NullType, typename T07 = NullType, typename T08 = NullType, typename T09 = NullType, typename T10 = NullType, 
    typename T11 = NullType, typename T12 = NullType, typename T13 = NullType, typename T14 = NullType, typename T15 = NullType, 
    typename T16 = NullType, typename T17 = NullType, typename T18 = NullType, typename T19 = NullType, typename T20 = NullType
>
class Typelist 
{
private:
    typedef typename Typelist<T02, T03, T04, T05, T06, T07, T08, T09, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20>::Type TailType;

public:
    typedef typename TypelistNode<T01, TailType> Type;
};

//=============================================================================
template <>
class Typelist<> 
{
public:
    typedef NullType Type;
};


namespace TL 
{

//=============================================================================
//
// Computes the length of a type list excluding the tailing NullType
//
//=============================================================================

template <class T> struct Length;

//=============================================================================
template <typename T, typename U>
struct Length< TypelistNode<T, U> >
{
    enum { Value = 1 + Length<U>::Value };
};

//=============================================================================
template <>
struct Length<NullType>
{
    enum { Value = 0 };
};

}; // namespace TL







