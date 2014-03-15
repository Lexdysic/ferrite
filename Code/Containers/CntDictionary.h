
#include <map>

namespace Internal
{

//==================================================================================================
//
// TDictionaryBase<K, V>
//
//==================================================================================================
template <typename K, typename V>
class TDictionaryBase
{
public:
    TDictionaryBase ();
    TDictionaryBase (const TDictionaryBase<K, V> & rhs);
    TDictionaryBase (TDictionaryBase<K, V> && rhs);
    ~TDictionaryBase ();
    
    uint Count () const;
    void Clear ();
    bool Contains (const K & key) const;

    void Set (const K & key, const V & value);
    void Set (K && key, V && value);
    void Delete (const K & key);

public:

    typedef typename std::map<K, V>::iterator iterator;

    iterator begin ();
    iterator end ();

protected:
    std::map<K, V> m_map;
};

} // namespace Internal



//==================================================================================================
//
// TDictionary<K, V>
//
//==================================================================================================
template <typename K, typename V>
class TDictionary :
    public Internal::TDictionaryBase<K, V>
{
public:
    TDictionary ();
    TDictionary (const TDictionary<K, V> & rhs);
    TDictionary (TDictionary<K, V> && rhs);
    ~TDictionary ();

    V * Find (const K & key);
    const V * Find (const K & key) const;
};



//==================================================================================================
//
// TDictionary<K, V *>
//
//==================================================================================================
template <typename K, typename V>
class TDictionary<K, V *> :
    public Internal::TDictionaryBase<K, V *>
{
public:
    TDictionary ();
    ~TDictionary ();

    V * Find (const K & key);
    const V * Find (const K & key) const;
};

