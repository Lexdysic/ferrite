


//*****************************************************************************
//
// TId
//
//*****************************************************************************

//=============================================================================
template <typename Tag, typename T> const TId<Tag, T> TId<Tag, T>::Invalid(0);
template <typename Tag, typename T> const TId<Tag, T> TId<Tag, T>::Null(0);

//=============================================================================
template <typename Tag, typename T>
TId<Tag, T>::TId () :
    m_id(0)
{
}

//=============================================================================
template <typename Tag, typename T>
TId<Tag, T>::TId (T id) :
    m_id(id)
{
}

//=============================================================================
template <typename Tag, typename T>
TId<Tag, T> & TId<Tag, T>::operator++ ()
{
    m_id++;
    return *this;
}

//=============================================================================
template <typename Tag, typename T>
TId<Tag, T> & TId<Tag, T>::operator++ (int)
{
    m_id++;
    return *this;
}

//=============================================================================
template <typename Tag, typename T> bool operator== (TId<Tag, T> lhs, TId<Tag, T> rhs) { return lhs.m_id == rhs.m_id; }
template <typename Tag, typename T> bool operator!= (TId<Tag, T> lhs, TId<Tag, T> rhs) { return lhs.m_id != rhs.m_id; }
template <typename Tag, typename T> bool operator<  (TId<Tag, T> lhs, TId<Tag, T> rhs) { return lhs.m_id <  rhs.m_id; }
template <typename Tag, typename T> bool operator<= (TId<Tag, T> lhs, TId<Tag, T> rhs) { return lhs.m_id <= rhs.m_id; }
template <typename Tag, typename T> bool operator>  (TId<Tag, T> lhs, TId<Tag, T> rhs) { return lhs.m_id >  rhs.m_id; }
template <typename Tag, typename T> bool operator>= (TId<Tag, T> lhs, TId<Tag, T> rhs) { return lhs.m_id >= rhs.m_id; }



//*****************************************************************************
//
// TIdDataSerial
//
//*****************************************************************************

//=============================================================================
template <typename T>
TIdDataSerial<T>::TIdDataSerial () :
    m_nextId(1)
{
}

//=============================================================================
template <typename T>
T TIdDataSerial<T>::New ()
{
    return m_nextId++;
}

//=============================================================================
template <typename T>
void TIdDataSerial<T>::Delete (T id)
{
    // Nothing...
}



//*****************************************************************************
//
// TIdDataPacked
//
//*****************************************************************************

//=============================================================================
template <typename T>
TIdDataPacked<T>::TIdDataPacked ()
{
}

//=============================================================================
template <typename T>
T TIdDataPacked<T>::New ()
{
    if (m_free.IsEmpty())
        return m_next.New();

    const T id = *m_free.Top();
    m_free.DeleteOrdered(m_free.Count() - 1);
    return id;
}

//=============================================================================
template <typename T>
void TIdDataPacked<T>::Delete (T id)
{
    m_free.Add(id);
}



//*****************************************************************************
//
// TIdManager
//
//*****************************************************************************

//=============================================================================
template <typename A>
typename TIdManager<A>::T TIdManager<A>::New ()
{
    return m_allocator.New();
}

//=============================================================================
template <typename A>
void TIdManager<A>::Delete (T id)
{
    m_allocator.Delete(id);
}
