#ifdef MATHFIXED_H
#  error "Cannot include header more than once."
#endif
#define MATHFIXED_H

//*****************************************************************************
//
// TFixed
//
//*****************************************************************************

template <typename T = sint16, uint32 magnitudeBits = 1, uint32 fractionalBits = 14> 
class TFixed 
{
    static_assert(
        magnitudeBits + fractionalBits + 1 == sizeof(T) * std::numeric_limits<unsigned char>::digits,
        "The total count of bits must match the field size"
    );

public:
    explicit TFixed (float32 f);
    inline TFixed (T sign, T magnitude, T fractional);
    inline TFixed (T bits);

    float32 ToFloat() const;

    static float32 ApproxMax ();
    static float32 ApproxMin ();
    static float32 ApproxResolution ();

private:
    T mBits;

    static const uint32 BITS = magnitudeBits + fractionalBits + 1;
    static const T      K    = 1 << (fractionalBits-1);

    static const uint32 BITOFFSET_FRACTIONAL = 0;
    static const uint32 BITOFFSET_MAGNITUDE  = fractionalBits;
    static const uint32 BITOFFSET_SIGN       = magnitudeBits + fractionalBits;

    static const T      BITMASK_SIGN       = 1 << (magnitudeBits + fractionalBits);
    static const T      BITMASK_FRACTIONAL = (1 << fractionalBits) - 1;
    static const T      BITMASK_MAGNITUDE  = (BITMASK_SIGN - 1) & ~BITMASK_FRACTIONAL;

};

template <typename T, uint32 M, uint32 F> 
inline TFixed<T,M,F> operator+ (const TFixed<T,M,F> & lhs, const TFixed<T,M,F> & rhs);

template <typename T, uint32 M, uint32 F> 
inline TFixed<T,M,F> operator- (const TFixed<T,M,F> & lhs, const TFixed<T,M,F> & rhs);

template <typename T, uint32 M, uint32 F> 
inline TFixed<T,M,F> operator* (const TFixed<T,M,F> & lhs, const TFixed<T,M,F> & rhs);

template <typename T, uint32 M, uint32 F> 
inline TFixed<T,M,F> operator/ (const TFixed<T,M,F> & lhs, const TFixed<T,M,F> & rhs);