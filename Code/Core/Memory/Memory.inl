
//=============================================================================
void MemSet (void * ptr, uint bytes, byte value)
{
    memset(ptr, value, bytes);
}

//=============================================================================
void MemCopy (void * destination, const void * source, uint bytes)
{
    memcpy(destination, source, bytes);
}

//=============================================================================
template <typename T>
void MemCopy (T & destination, const T & source)
{
    MemCopy(&destination, source, sizeof(source));
}

//=============================================================================
template <typename T>
void MemCopy (T *& destination, const T *& source)
{
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
bool MemEqual (const void * a, const void * b, uint bytes)
{
    return memcmp(a, b, bytes) == 0;
}

//=============================================================================
void MemZero (void * ptr, uint bytes)
{
    MemSet(ptr, bytes, 0);
}

//=============================================================================
template <typename T>
void MemZero (T & pod)
{
    MemZero(&pod, sizeof(T));
}

//=============================================================================
template <typename T>
void MemZero (T *& pod)
{
    MemZero(pod, sizeof(T));
}

//=============================================================================
template <typename T, uint N>
void MemZero (T (& arr)[N])
{
    MemZero(arr, sizeof(arr));
}