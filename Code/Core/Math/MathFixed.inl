//==================================================================================================
//
// File:    MathFixed.h
// Author:  Jason Jackson
// Date:    May 19, 2009
//
// Fixed point math utilities
//
//=================================================================================================

//=============================================================================
template <typename T, uint32 M, uint32 F> 
Fixed<T, M, F>::Fixed(float32 f) 
{
    mBits = T(f * (1 << F));
}

//=============================================================================
template <typename T, uint32 M, uint32 F> 
Fixed<T, M, F>::Fixed(T sign, T magnitude, T fractional)
{
    mBits = 
        (sign       << BITOFFSET_SIGN)       & BITMASK_SIGN |
        (magnitude  << BITOFFSET_MAGNITUDE)  & BITMASK_MAGNITUDE | 
        (fractional << BITOFFSET_FRACTIONAL) & BITMASK_FRACTIONAL;
}

//=============================================================================
template <typename T, uint32 M, uint32 F> 
Fixed<T, M, F>::Fixed(T bits) 
{
    mBits = bits;
}

//=============================================================================
template <typename T, uint32 M, uint32 F> 
float32 Fixed<T, M, F>::ToFloat() const 
{
    return float32(mBits) / float32(1 << F);
}

//=============================================================================
template <typename T, uint32 M, uint32 F> 
inline Fixed<T,M,F> operator+( const Fixed<T,M,F> & lhs, const Fixed<T,M,F> & rhs )
{
    return Fixed(lhs.mBits + rhs.mBits);
}

//=============================================================================
template <typename T, uint32 M, uint32 F> 
inline Fixed<T,M,F> operator-( const Fixed<T,M,F> & lhs, const Fixed<T,M,F> & rhs )
{
    return Fixed(lhs.mBits - rhs.mBits);
}

//=============================================================================
template <typename T, uint32 M, uint32 F> 
inline Fixed<T,M,F> operator*( const Fixed<T,M,F> & lhs, const Fixed<T,M,F> & rhs )
{
    long T temp = (long T)lhs.mBits * (long T)rhs.mBits;
    temp += K;
    temp >>= F;
    return Fixed(temp);

}

//=============================================================================
template <typename T, uint32 M, uint32 F> 
inline Fixed<T,M,F> operator/( const Fixed<T,M,F> & lhs, const Fixed<T,M,F> & rhs )
{
#pragma message("Implement this")
}