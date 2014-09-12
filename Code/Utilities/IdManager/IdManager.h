

//*****************************************************************************
//
// TId
//
//*****************************************************************************

template <typename Tag, typename T = uint>
class TId
{
public:
    inline TId ();
    inline explicit TId (T id);

    inline TId & operator++ ();
    inline TId & operator++ (int);

    template <typename Tag, typename T> friend bool operator== (TId<Tag, T>, TId<Tag, T>);
    template <typename Tag, typename T> friend bool operator!= (TId<Tag, T>, TId<Tag, T>);
    template <typename Tag, typename T> friend bool operator<  (TId<Tag, T>, TId<Tag, T>);
    template <typename Tag, typename T> friend bool operator<= (TId<Tag, T>, TId<Tag, T>);
    template <typename Tag, typename T> friend bool operator>  (TId<Tag, T>, TId<Tag, T>);
    template <typename Tag, typename T> friend bool operator>= (TId<Tag, T>, TId<Tag, T>);

public:

    static const TId Invalid;
    static const TId Null;

private:
    T m_id;
};

template <typename Tag, typename T> inline bool operator== (TId<Tag, T> lhs, TId<Tag, T> rhs);
template <typename Tag, typename T> inline bool operator!= (TId<Tag, T> lhs, TId<Tag, T> rhs);
template <typename Tag, typename T> inline bool operator<  (TId<Tag, T> lhs, TId<Tag, T> rhs);
template <typename Tag, typename T> inline bool operator<= (TId<Tag, T> lhs, TId<Tag, T> rhs);
template <typename Tag, typename T> inline bool operator>  (TId<Tag, T> lhs, TId<Tag, T> rhs);
template <typename Tag, typename T> inline bool operator>= (TId<Tag, T> lhs, TId<Tag, T> rhs);



//*****************************************************************************
//
// TIdDataSerial
//
//*****************************************************************************

template <typename T>
class TIdDataSerial
{
public:
    typedef T Type;

    TIdDataSerial ();

    T New ();
    void Delete (T id);

private:
    T m_nextId;
};



//*****************************************************************************
//
// TIdDataPacked
//
//*****************************************************************************

template <typename T>
class TIdDataPacked
{
public:
    typedef T Type;

    TIdDataPacked ();

    T New ();
    void Delete (T id);

private:
    TIdDataSerial m_next;
    TArray<T>     m_free;
};



//*****************************************************************************
//
// TIdManager
//
//*****************************************************************************

template <typename Allocator>
class TIdManager
{
public:
    typedef typename Allocator::Type T;
    
    T New ();
    void Delete (T id);

private:
    Allocator m_allocator;
};


// C++11 helper definitions
//template <typename T>
//using TIdManagerSerial<T> = TIdManager<TIdDataSerial<T>>;
//
//template <typename T>
//using TIdManagerPacked<T> = TIdManager<TIdDataPacked<T>>;

#include "IdManager.inl"