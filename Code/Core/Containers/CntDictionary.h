
#include <map>

namespace Containers
{

namespace Internal
{

//*****************************************************************************
//
// TDictionaryBase<K, V>
//
//*****************************************************************************

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

    friend bool operator== (const TDictionaryBase<K, V> & lhs, const TDictionaryBase<K, V> & rhs) { return lhs.m_map == rhs.m_map; }

public:

    typedef typename std::map<K, V>::iterator iterator;
    typedef typename std::map<K, V>::const_iterator const_iterator;

    iterator begin ();
    iterator end ();
    const_iterator begin () const;
    const_iterator end () const;

protected:

    std::map<K, V> m_map;
};

}} // namespace Containers::Internal




//*****************************************************************************
//
// TDictionary<K, V>
//
//*****************************************************************************

template <typename K, typename V>
class TDictionary :
    public Containers::Internal::TDictionaryBase<K, V>
{
public:
    TDictionary ();
    TDictionary (const TDictionary<K, V> & rhs);
    TDictionary (TDictionary<K, V> && rhs);
    ~TDictionary ();

    V * Find (const K & key);
    const V * Find (const K & key) const;
    const V & Find (const K & key, const V & defaultValue) const;
};



//*****************************************************************************
//
// TDictionary<K, V *>
//
//*****************************************************************************

template <typename K, typename V>
class TDictionary<K, V *> :
    public Containers::Internal::TDictionaryBase<K, V *>
{
public:
    TDictionary ();
    ~TDictionary ();

    V * Find (const K & key);
    const V * Find (const K & key) const;
};

