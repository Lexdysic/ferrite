
//=============================================================================
template <typename T>
TArray<T>::TArray ()
{

}

 //=============================================================================
template <typename T>
TArray<T>::TArray (const TArray<T> & rhs) :
    m_array(rhs.m_array)
{
}

//=============================================================================
template <typename T>
TArray<T>::TArray (TArray<T> && rhs) :
    m_array(std::forward<std::vector<T>>(rhs.m_array))
{
}

//=============================================================================
template <typename T>
TArray<T>::~TArray ()
{

}

//=============================================================================
template <typename T>
TArray<T> & TArray<T>::operator= (TArray<T> && rhs)
{
    m_array = std::forward<std::vector<T>>(rhs.m_array);
    return *this;
}

//=============================================================================
template <typename T>
bool TArray<T>::IsEmpty () const
{
    return m_array.empty();
}

//=============================================================================
template <typename T>
void TArray<T>::Add (const T & value)
{
    m_array.push_back(value);
}

//=============================================================================
template <typename T>
void TArray<T>::Add (T && value)
{
    m_array.push_back(value);
}

//=============================================================================
template <typename T>
void TArray<T>::Add (const TArray<T> & arr)
{
    m_array.insert(m_array.end(), arr.m_array.begin(), arr.m_array.end());
}

//=============================================================================
template <typename T>
void TArray<T>::Add (const T values[], uint count)
{
    m_array.insert(m_array.end(), values, values + count);
}

//=============================================================================
template <typename T>
T * TArray<T>::New ()
{
    m_array.push_back(T());
    return &m_array.back();
}

//=============================================================================
template <typename T>
void TArray<T>::RemoveUnordered (uint index)
{
    m_array[index] = m_array[Count() - 1];
    m_array.pop_back();
}

//=============================================================================
template <typename T>
void TArray<T>::RemoveOrdered (uint index)
{
    m_array.erase(m_array.begin() + index);
}

//=============================================================================
template <typename T>
void TArray<T>::Clear ()
{
    m_array.clear();
}

//=============================================================================
template <typename T>
void TArray<T>::Reserve (uint count)
{
    m_array.reserve(count);
}

//=============================================================================
template <typename T>
void TArray<T>::ReserveAdditional (uint count)
{
    m_array.reserve(Count() + count);
}

//=============================================================================
template <typename T>
void TArray<T>::Resize (uint count)
{
    m_array.resize(count);
}

//=============================================================================
template <typename T>
uint TArray<T>::Find (const T & value) const
{
    auto it = std::find(m_array.begin(), m_array.end(), value);
    return it - m_array.begin();
}

//=============================================================================
template <typename T>
template <typename U>
uint TArray<T>::Find (const U & value) const
{
    auto it = std::find(m_array.begin(), m_array.end(), value);
    return it - m_array.begin();
}

//=============================================================================
template <typename T>
bool TArray<T>::Contains (const T & value) const
{
    return Find(value) < Count();
}

//=============================================================================
template <typename T>
uint TArray<T>::Index (const T * ptr) const
{
    const ptrdiff_t index = ptr - Ptr();
    if (Math::IsInRange<ptrdiff_t>(index, 0, Count()))
        return index;
    return (uint)-1;
}

//=============================================================================
template <typename T>
T * TArray<T>::Ptr ()
{
    return m_array.data();
}

//=============================================================================
template <typename T>
const T * TArray<T>::Ptr () const
{
    return m_array.data();
}

//=============================================================================
template <typename T>
T * TArray<T>::Term ()
{
    return Ptr() + Count();
}

//=============================================================================
template <typename T>
const T * TArray<T>::Term () const
{
    return Ptr() + Count();
}

//=============================================================================
template <typename T>
T * TArray<T>::Top ()
{
    ASSERT(Count() > 0);
    return Ptr() + Count() - 1;
}

//=============================================================================
template <typename T>
const T * TArray<T>::Top () const
{
    ASSERT(Count() > 0);
    return Ptr() + Count() - 1;
}

//=============================================================================
template <typename T>
uint TArray<T>::Count () const
{
    return m_array.size();
}

//=============================================================================
template <typename T>
const T & TArray<T>::operator[] (uint index) const
{
    return m_array[index];
}

//=============================================================================
template <typename T>
T & TArray<T>::operator[] (uint index)
{
    return m_array[index];
}


//=============================================================================
template <typename Y>
bool operator== (const TArray<Y> & lhs, const TArray<Y> & rhs)
{
    return lhs.m_array == rhs.m_array;
}

//=============================================================================
template <typename Y>
bool operator< (const TArray<Y> & lhs, const TArray<Y> & rhs)
{
    return lhs.m_array < rhs.m_array;
}