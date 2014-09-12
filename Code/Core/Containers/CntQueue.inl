
//*****************************************************************************
//
// TQueue
//
//*****************************************************************************

//=============================================================================
template <typename T>
TQueue<T>::TQueue ()
{
}

//=============================================================================
template <typename T>
TQueue<T>::TQueue (const TQueue<T> & rhs) :
    m_data(rhs.m_data)
{
}

//=============================================================================
template <typename T>
TQueue<T>::TQueue (TQueue<T> && rhs) :
    m_data(std::forward(rhs.m_data))
{
}

//=============================================================================
template <typename T>
TQueue<T>::~TQueue ()
{
}

//=============================================================================
template <typename T>
TQueue<T> & TQueue<T>::operator= (TQueue<T> && rhs)
{
    return m_data == rhs.m_data;
}

//=============================================================================
template <typename T>
bool TQueue<T>::IsEmpty () const
{
    return m_data.empty();
}

//=============================================================================
template <typename T>
void TQueue<T>::AddFront (const T & value)
{
    m_data.push_front(value);
}

//=============================================================================
template <typename T>
void TQueue<T>::AddFront (T && value)
{
    m_data.push_front(std::forward(value));
}

//=============================================================================
template <typename T>
void TQueue<T>::AddFront (const TArray<T> & arr)
{
    for (const T & value : arr)
        AddFront(value);
}

//=============================================================================
template <typename T>
void TQueue<T>::AddFront (const T values[], uint count)
{
    for (const T * ptr = value, term = values + count; ptr < term; ++ptr)
        AddFront(*ptr);
}

//=============================================================================
template <typename T>
void TQueue<T>::AddBack (const T & value)
{
    m_data.push_back(value);
}

//=============================================================================
template <typename T>
void TQueue<T>::AddBack (T && value)
{
    m_data.push_back(std::forward(value));
}

//=============================================================================
template <typename T>
void TQueue<T>::AddBack (const TArray<T> & arr)
{
    for (const T & value : arr)
        AddBack(value);
}

//=============================================================================
template <typename T>
void TQueue<T>::AddBack (const T values[], uint count)
{
    const T * ptr = values;
    const T * term = values + count;
    for ( ; ptr < term; ++ptr)
        AddBack(*ptr);
}

//=============================================================================
template <typename T>
void TQueue<T>::RemoveFront ()
{
    m_data.pop_front();
}

//=============================================================================
template <typename T>
void TQueue<T>::RemoveBack ()
{
    m_data.pop_back();
}

//=============================================================================
template <typename T>
void TQueue<T>::Remove (uint index)
{
    m_data.erase(std::next(m_data.begin(), index));
}

//=============================================================================
template <typename T>
void TQueue<T>::Remove (uint first, uint term)
{
    m_data.erase(
        std::next(m_data.begin(), first),
        std::next(m_data.begin(), term)
    );
}

//=============================================================================
template <typename T>
void TQueue<T>::Clear ()
{
    m_data.clear();
}

//=============================================================================
template <typename T>
uint TQueue<T>::Find (const T & value) const
{
    auto it = std::find(m_data.begin(), m_data.end(), value);
    if (it == m_data.end())
        return UINT_MAX;
    return std::distance(it, m_data.begin());
}

//=============================================================================
template <typename T>
template <typename U>
uint TQueue<T>::Find (const U & value) const
{
    auto it = std::find(m_data.begin(), m_data.end(), value);
    if (it == m_data.end())
        return UINT_MAX;
    return std::distance(it, m_data.begin());
}

//=============================================================================
template <typename T>
bool TQueue<T>::Contains (const T & value) const
{
    return Find(value) < Count();
}

//=============================================================================
template <typename T>
uint TQueue<T>::Count () const
{
    return m_data.size();
}

//=============================================================================
template <typename T>
const T & TQueue<T>::operator[] (sint index) const
{
    ASSERT(Math::IsInRange(index, -(sint)Count(), (sint)Count()));
    const uint i = (index < 0) ? (Count()+index) : index;
    return m_data[i];
}

//=============================================================================
template <typename T>
T & TQueue<T>::operator[] (sint index)
{
    ASSERT(Math::IsInRange(index, -(sint)Count(), (sint)Count()));
    const uint i = (index < 0) ? (Count()+index) : index;
    return m_data[i];
}

//=============================================================================
template <typename T>
typename TQueue<T>::CConstIterator TQueue<T>::begin () const
{
    return m_data.cbegin();
}

//=============================================================================
template <typename T>
typename TQueue<T>::CIterator TQueue<T>::begin ()
{
    return m_data.begin();
}

//=============================================================================
template <typename T>
typename TQueue<T>::CConstIterator TQueue<T>::end () const
{
    return m_data.cend();
}

//=============================================================================
template <typename T>
typename TQueue<T>::CIterator TQueue<T>::end ()
{
    return m_data.end();
}