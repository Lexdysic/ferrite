#include <queue>

template <typename T>
class TQueue
{
public:
    inline TQueue ();
    inline TQueue (const TQueue<T> & rhs);
    inline TQueue (TQueue<T> && rhs);
    inline ~TQueue ();

    inline TQueue<T> & operator= (TQueue<T> && rhs);

    inline bool IsEmpty () const;

    inline void AddFront (const T & value);
    inline void AddFront (T && value);
    inline void AddFront (const TArray<T> & arr);
    inline void AddFront (const T values[], uint count);
    inline void AddBack (const T & value);
    inline void AddBack (T && value);
    inline void AddBack (const TArray<T> & arr);
    inline void AddBack (const T values[], uint count);
    inline void RemoveFront ();
    inline void RemoveBack ();
    inline void Remove (uint index);
    inline void Remove (uint first, uint term);
    inline void Clear ();

    inline uint Find (const T & value) const;
    template <typename U>
    inline uint Find (const U & value) const;
    inline bool Contains (const T & value) const;

    inline uint Count () const;
    inline const T & operator[] (sint index) const;
    inline T &       operator[] (sint index);

public:

    typedef typename std::deque<T>::iterator CIterator;

public:

    template <typename Y>
    friend bool operator== (const TQueue<Y> & lhs, const TQueue<Y> & rhs);

    template <typename Y>
    friend bool operator<  (const TQueue<Y> & lhs, const TQueue<Y> & rhs);

public:
    
    CIterator begin ();
    const CIterator begin () const;

    CIterator end ();
    const CIterator end () const;

private:

    std::deque<T> m_data;
};