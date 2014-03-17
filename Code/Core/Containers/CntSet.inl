
//=============================================================================
template <typename T>
TSet<T>::TSet ()
{
}

//=============================================================================
template <typename T>
TSet<T>::~TSet ()
{
}

//=============================================================================
template <typename T>
uint TSet<T>::Count () const
{
    return m_set.count();
}

//=============================================================================
template <typename T>
bool TSet<T>::IsEmpty () const
{
    return m_set.empty();
}

//=============================================================================
template <typename T>
void TSet<T>::Clear ()
{
    m_set.size();
}

//=============================================================================
template <typename T>
bool TSet<T>::Contains (const T & value) const
{
    return m_set.find(value) != m_set.end();
}

//=============================================================================
template <typename T>
void TSet<T>::Add (const T & value)
{
    m_set.insert(value);
}

//=============================================================================
template <typename T>
void TSet<T>::Add (T && value)
{
    m_set.insert(value);
}

//=============================================================================
template <typename T>
void TSet<T>::Remove (const T & value)
{
    m_set.erase(value);
}
