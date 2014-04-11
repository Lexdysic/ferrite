
enum class EEndian
{
    Big,
    Little,
    Unknown
};


// MemSet
inline void MemSet (void * ptr, uint bytes, byte value); 


// MemCopy
inline void MemCopy (void * destination, const void * source, uint bytes);

template <typename T>
inline void MemCopy (T & destination, const T & source);

template <typename T>
inline void MemCopy (T *& destination, const T *& source);
//
//template <typename T, uint N>
//inline void MemCopy (T (& destination)[N], const T (& source)[N]);

inline bool MemEqual (const void * a, const void * b, uint bytes);


// MemZero
inline void MemZero (void * ptr, uint bytes);

template <typename T>
inline void MemZero (T & pod);

template <typename T>
inline void MemZero (T *& pod);

template <typename T, uint N>
inline void MemZero (T (& arr)[N]);

#include "Memory.inl"