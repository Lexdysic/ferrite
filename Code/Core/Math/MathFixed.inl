
//*****************************************************************************
//
// TFixed
//
//*****************************************************************************

//=============================================================================
template <typename T, uint32 M, uint32 F> 
TFixed<T, M, F>::TFixed (float32 f) 
{
    mBits = T(f * (1 << F));
}

//=============================================================================
template <typename T, uint32 M, uint32 F> 
TFixed<T, M, F>::TFixed (T sign, T magnitude, T fractional)
{
    mBits = 
        (sign       << BITOFFSET_SIGN)       & BITMASK_SIGN |
        (magnitude  << BITOFFSET_MAGNITUDE)  & BITMASK_MAGNITUDE | 
        (fractional << BITOFFSET_FRACTIONAL) & BITMASK_FRACTIONAL;
}

//=============================================================================
template <typename T, uint32 M, uint32 F> 
TFixed<T, M, F>::TFixed (T bits) 
{
    mBits = bits;
}

//=============================================================================
template <typename T, uint32 M, uint32 F> 
float32 TFixed<T, M, F>::ToFloat () const 
{
    return float32(mBits) / float32(1 << F);
}

//=============================================================================
template <typename T, uint32 M, uint32 F> 
inline TFixed<T,M,F> operator+ (const TFixed<T,M,F> & lhs, const TFixed<T,M,F> & rhs)
{
    return TFixed(lhs.mBits + rhs.mBits);
}

//=============================================================================
template <typename T, uint32 M, uint32 F> 
inline TFixed<T,M,F> operator- (const TFixed<T,M,F> & lhs, const TFixed<T,M,F> & rhs)
{
    return TFixed(lhs.mBits - rhs.mBits);
}

//=============================================================================
template <typename T, uint32 M, uint32 F> 
inline TFixed<T,M,F> operator* (const TFixed<T,M,F> & lhs, const TFixed<T,M,F> & rhs)
{
    long T temp = (long T)lhs.mBits * (long T)rhs.mBits;
    temp += K;
    temp >>= F;
    return TFixed(temp);

}

//=============================================================================
template <typename T, uint32 M, uint32 F> 
inline TFixed<T,M,F> operator/ (const TFixed<T,M,F> & lhs, const TFixed<T,M,F> & rhs)
{
#pragma message("Implement this")
}