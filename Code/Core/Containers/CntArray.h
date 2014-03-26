#include <vector>

template <typename T>
class TArray
{
public:
    inline TArray ();
    inline TArray (const TArray<T> & rhs);
    inline TArray (TArray<T> && rhs);
    inline ~TArray ();

    inline TArray<T> & operator= (TArray<T> && rhs);

    inline bool IsEmpty () const;

    inline void Add (const T & value);
    inline void Add (T && value);
    inline void Add (const TArray<T> & arr);
    inline void Add (const T values[], uint count);
    inline T *  New ();
    inline void RemoveUnordered (uint index);
    inline void RemoveOrdered (uint index);
    inline void Clear ();
    inline void Reserve (uint count);
    inline void ReserveAdditional (uint count);
    inline void Resize (uint count);

    inline uint Find (const T & value) const;
    template <typename U>
    inline uint Find (const U & value) const;
    inline bool Contains (const T & value) const;
    inline uint Index (const T * ptr) const;

    inline T * Ptr ();
    inline const T * Ptr () const;
    inline T * Term ();
    inline const T * Term () const;
    inline T * Top ();
    inline const T * Top () const;
    inline uint Count () const;
    inline const T & operator[] (uint index) const;
    inline T &       operator[] (uint index);

public:

    template <typename Y>
    friend bool operator== (const TArray<Y> & lhs, const TArray<Y> & rhs);

    template <typename Y>
    friend bool operator<  (const TArray<Y> & lhs, const TArray<Y> & rhs);

private:
    std::vector<T> m_array;
};

template <typename T>
const T * begin (const TArray<T> & array) { return array.Ptr(); }
template <typename T>
T * begin (TArray<T> & array) { return array.Ptr(); }


template <typename T>
const T * end (const TArray<T> & array) { return array.Term(); }
template <typename T>
T * end (TArray<T> & array) { return array.Term(); }