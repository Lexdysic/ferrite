
#include <set>

//*****************************************************************************
//
// TSet
//
//*****************************************************************************

template <typename T>
class TSet
{
public:
    TSet ();
    ~TSet ();
    
    uint Count () const;
    bool IsEmpty () const;

    void Clear ();
    bool Contains (const T & key) const;

    void Add (const T & value);
    void Add (T && value);
    void Remove (const T & key);

private:
    std::set<T> m_set;
};
