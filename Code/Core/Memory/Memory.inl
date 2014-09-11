


//=============================================================================
//
// MemSet
//
//=============================================================================

//=============================================================================
void MemSet (void * ptr, uint bytes, byte value)
{
    memset(ptr, value, bytes);
}



//=============================================================================
//
// MemCopy
//
//=============================================================================

//=============================================================================
void MemCopy (void * destination, const void * source, uint bytes)
{
    memcpy(destination, source, bytes);
}

//=============================================================================
template <typename T>
void MemCopy (T & destination, const T & source)
{
    static_assert(std::is_pod<T>::value, "must be POD type");
    MemCopy(&destination, source, sizeof(source));
}

//=============================================================================
template <typename T>
void MemCopy (T *& destination, const T *& source)
{
    static_assert(std::is_pod<T>::value, "must be POD type");
    MemCopy(destination, source, sizeof(T));
}
//
////=============================================================================
//template <typename T, uint N>
//void MemCopy (T (& destination)[N], const T (& source)[N])
//{
//    MemCopy(destination, source, sizeof(source));
//}



//=============================================================================
//
// MemEqual
//
//=============================================================================

//=============================================================================
bool MemEqual (const void * a, const void * b, uint bytes)
{
    return memcmp(a, b, bytes) == 0;
}



//=============================================================================
//
// MemZero
//
//=============================================================================

//=============================================================================
void MemZero (void * ptr, uint bytes)
{
    MemSet(ptr, bytes, 0);
}

//=============================================================================
template <typename T>
void MemZero (T & pod)
{
    static_assert(std::is_pod<T>::value, "must be POD type");
    MemZero(&pod, sizeof(T));
}

//=============================================================================
template <typename T>
void MemZero (T *& pod)
{
    static_assert(std::is_pod<T>::value, "must be POD type");
    MemZero(pod, sizeof(T));
}

//=============================================================================
template <typename T, uint N>
void MemZero (T (& arr)[N])
{
    static_assert(std::is_pod<T>::value, "must be POD type");
    MemZero(arr, sizeof(arr));
}