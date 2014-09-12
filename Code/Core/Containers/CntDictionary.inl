
namespace Containers {
namespace Internal {


//*****************************************************************************
//
// TDictionaryBase<K, V>
//
//*****************************************************************************

//=============================================================================
template <typename K, typename V>
TDictionaryBase<K, V>::TDictionaryBase ()
{
}

//=============================================================================
template <typename K, typename V>
TDictionaryBase<K, V>::TDictionaryBase (const TDictionaryBase<K, V> & rhs) :
    m_map(rhs.m_map)
{
}

//=============================================================================
template <typename K, typename V>
TDictionaryBase<K, V>::TDictionaryBase (TDictionaryBase<K, V> && rhs) :
    m_map(std::move(rhs.m_map))
{
}

//=============================================================================
template <typename K, typename V>
TDictionaryBase<K, V>::~TDictionaryBase ()
{
    Clear();
}

//=============================================================================
template <typename K, typename V>
uint TDictionaryBase<K, V>::Count () const
{
    return m_map.size();
}

//=============================================================================
template <typename K, typename V>
void TDictionaryBase<K, V>::Clear ()
{
    m_map.clear();
}

//=============================================================================
template <typename K, typename V>
bool TDictionaryBase<K, V>::Contains (const K & key) const
{
    return m_map.find(key) != m_map.end();
}

//=============================================================================
template <typename K, typename V>
void TDictionaryBase<K, V>::Set (const K & key, const V & value)
{
    m_map[key] = value;
}

//=============================================================================
template <typename K, typename V>
void TDictionaryBase<K, V>::Set (K && key, V && value)
{
    m_map[std::forward<K>(key)] = std::forward<V>(value);
}

//=============================================================================
template <typename K, typename V>
void TDictionaryBase<K, V>::Delete (const K & key)
{
    m_map.erase(key);
}

//=============================================================================
template <typename K, typename V>
typename TDictionaryBase<K, V>::iterator TDictionaryBase<K, V>::begin ()
{
    return m_map.begin();
}

//=============================================================================
template <typename K, typename V>
typename TDictionaryBase<K, V>::iterator TDictionaryBase<K, V>::end ()
{
    return m_map.end();
}

//=============================================================================
template <typename K, typename V>
typename TDictionaryBase<K, V>::const_iterator TDictionaryBase<K, V>::begin () const
{
    return m_map.begin();
}

//=============================================================================
template <typename K, typename V>
typename TDictionaryBase<K, V>::const_iterator TDictionaryBase<K, V>::end () const
{
    return m_map.end();
}

}} // namespace Containers::Internal



//*****************************************************************************
//
// TDictionary<K, V>
//
//*****************************************************************************

//=============================================================================
template <typename K, typename V>
TDictionary<K, V>::TDictionary ()
{
}

//=============================================================================
template <typename K, typename V>
TDictionary<K, V>::TDictionary (const TDictionary<K, V> & rhs) :
    TDictionaryBase<K, V>(rhs)
{
}

//=============================================================================
template <typename K, typename V>
TDictionary<K, V>::TDictionary (TDictionary<K, V> && rhs) :
    TDictionaryBase<K, V>(std::forward<TDictionary<K, V>>(rhs))
{
}

//=============================================================================
template <typename K, typename V>
TDictionary<K, V>::~TDictionary ()
{
}

//=============================================================================
template <typename K, typename V>
V * TDictionary<K, V>::Find (const K & key)
{
    auto it = m_map.find(key);
    if (it == m_map.end())
        return null;

    return &it->second;
}

//=============================================================================
template <typename K, typename V>
const V * TDictionary<K, V>::Find (const K & key) const
{
    auto it = m_map.find(key);
    if (it == m_map.end())
        return null;

    return &it->second;
}

//=============================================================================
template <typename K, typename V>
const V & TDictionary<K, V>::Find (const K & key, const V & defaultValue) const
{
    auto it = m_map.find(key);
    if (it == m_map.end())
        return defaultValue;

    return it->second;
}



//*****************************************************************************
//
// TDictionary<K, V *>
//
//*****************************************************************************

//=============================================================================
template <typename K, typename V>
TDictionary<K, V *>::TDictionary ()
{
}

//=============================================================================
template <typename K, typename V>
TDictionary<K, V *>::~TDictionary ()
{
}

//=============================================================================
template <typename K, typename V>
V * TDictionary<K, V *>::Find (const K & key)
{
    auto it = m_map.find(key);
    if (it == m_map.end())
        return null;

    return it->second;
}

//=============================================================================
template <typename K, typename V>
const V * TDictionary<K, V *>::Find (const K & key) const
{
    auto it = m_map.find(key);
    if (it == m_map.end())
        return null;

    return it->second;
}
