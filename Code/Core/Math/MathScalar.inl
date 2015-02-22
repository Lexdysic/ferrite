
//=============================================================================
template <typename T>
T Sign (const T & x)
{
    //static_assert(Meta::IsSigned<T>::value, "Cannot get the sign of an unsigned type");

    if (x < T(0))
        return T(-1);
    else if (x > T(0))
        return T(1);
    else
        return T(0);
}

//=============================================================================
template <typename T>
T Sq (const T & x)
{
    //static_assert(Meta::IsNumeric<T>::value, "Cannot square a non-numeric type.");
    return x * x;
}

//=============================================================================
template<> inline float32 Sqrt<float32> (float32 x) { return ::sqrtf(x); }
template<> inline float64 Sqrt<float64> (float64 x) { return ::sqrt(x); }

//=============================================================================
float32 Cos (Radian x)                { return ::cosf(x); }
float32 Sin (Radian x)                { return ::sinf(x); }
float32 Tan (Radian x)                { return ::tanf(x); }
Radian  ArcSin (float32 a)            { return Radian(::asinf(a)); }
Radian  ArcCos (float32 a)            { return Radian(::acosf(a)); }
Radian  ArcTan (float32 a)            { return Radian(::atanf(a)); }
Radian  ArcTan (float32 x, float32 y) { return Radian(::atan2f(y, x)); }

//=============================================================================
template<> inline float32 Floor (float32 x) { return ::floorf(x); }
template<> inline float64 Floor (float64 x) { return ::floor(x); }

//=============================================================================
template<> inline sint    FloorCast (const float32 & x) { return (sint)::floorf(x); }
template<> inline uint    FloorCast (const float32 & x) { return (uint)::floorf(x); }


//=============================================================================
template<> inline float32 Ceil<float32> (float32 x) { return ::ceilf(x); }
template<> inline float64 Ceil<float64> (float64 x) { return ::ceil(x); }

//=============================================================================
template<> inline float32 Frac<float32> (float32 x) { return x - Floor(x); }
template<> inline float64 Frac<float64> (float64 x) { return x - Floor(x); }

//=============================================================================
template <typename T>
T Abs (T x)
{
    //static_assert(Meta::IsSigned<T>::value, "Must used signed type");
    return (x < T(0)) ? -x : x;
}

//=============================================================================
float32 Pow (float32 b, float32 e) { return powf(b, e); }
float32 Exp (float32 x)            { return expf(x); }

//=============================================================================
float32 Log (float32 x)               { return log10f(x); }
float32 Ln (float32 x)                { return logf(x); }
float32 Lg (float32 x)                { return Log(x, 2.0f); }
float32 Log (float32 x, float32 base) { return Ln(x) / Ln(base); }

//=============================================================================
float32 Mod (float32 x, float32 r) { return fmodf(x, r); }

//=============================================================================
float32 Difference (float32 a, float32 b, float32 modulo)
{
    ASSERT(modulo > 0.0f);
    const float32 halfModulo = modulo * 0.5f;
    const float32 rawDistance = Abs(a - b);
    const float32 moduleDistance = Mod(rawDistance, modulo);
    return halfModulo - Abs(moduleDistance - halfModulo);
}

//=============================================================================
sint FloatToSint (float32 x)
{
    const float32 y = x - 0.5f;
    sint s;

    __asm fld y
    __asm fistp s

    return s;
}

//=============================================================================
sint FloatToSint (float64 x)
{
    return FloatToSint(float32(x));
}

//=============================================================================
uint FloatToUint (float32 x)
{
    uint u;

    __asm fld x
    __asm fistp u

    return u;
}

//=============================================================================
uint FloatToUint (float64 x)
{
    uint u;

    __asm fld x
    __asm fistp u

    return u;
}

//=============================================================================
sint64 FloatToSint64 (float32 x)
{
    sint64 i;

    __asm fld     x
    __asm fistp   i

    return i;
}

//=============================================================================
sint64 FloatToSint64 (float64 x)
{
    sint64 i;

    __asm fld     x
    __asm fistp   i

    return i;
}

//=============================================================================
template <typename T>
inline T Min (const T & a)
{
	return a;
}

//=============================================================================
template <typename T, typename... Ts>
T Min (const T & a, const T & b, const Ts &... args)
{
	return Min((a < b ? a : b), args...);
}

//=============================================================================
template <typename T>
inline T Max (const T & a)
{
	return a;
}

//=============================================================================
template <typename T, typename... Ts>
T Max (const T & a, const T & b, const Ts &... args)
{
	return Max((a > b ? a : b), args...);
}

//=============================================================================
template <typename T>
T Clamp (const T & x, const T & min, const T & max) 
{
    if (x > max)        return max;
    else if (x < min)	return min;
    else                return x;
}

//=============================================================================
template <typename T> 
T Lerp (const T & a, const T & b, float32 t)
{
    return (1.0f - t) * a + t * b;
}

//=============================================================================
template <typename T>
float InvLerp (const T & x, const T & a, const T & b)
{
    return (x - a) / (b - a);
}

//=============================================================================
float32 Inverse (float32 x)
{
    return 1.0f / x;
}

//=============================================================================
float64 Inverse (float64 x)
{
    return 1.0 / x;
}



namespace Math
{

//=============================================================================
uint BitCount (uint32 n)
{
	const uint32 MASK_01010101 = 0x55555555; // ((uint32)(-1)) / 3;
	const uint32 MASK_00110011 = 0x33333333; // ((uint32)(-1)) / 5;
	const uint32 MASK_00001111 = 0x0f0f0f0f; // ((uint32)(-1)) / 17;

    n = (n & MASK_01010101) + ((n >> 1) & MASK_01010101);
    n = (n & MASK_00110011) + ((n >> 2) & MASK_00110011);
    n = (n & MASK_00001111) + ((n >> 4) & MASK_00001111);

    return n % 255;
}

//=============================================================================
template <typename T>
bool IsInRange (const T & x, const T & a, const T & b)
{
    return a <= x && x <= b;
}

//=============================================================================
template <typename T>
T Map (const T & inMin, const T & inMax, const T & outMin, const T & outMax, const T & input)
{
    const float t = InvLerp(input, inMin, inMax);
    return Lerp(outMin, outMax, t);
}

//=============================================================================
template <typename T>
T MapClamp (const T & inMin, const T & inMax, const T & outMin, const T & outMax, const T & input)
{
    const float t = InvLerp(Clamp(input, inMin, inMax), inMin, inMax);
    return Lerp(outMin, outMax, t);
}

//=============================================================================
template <typename T>
bool IsPowerTwo (T value)
{
    return value != 0 && (value & (value - 1)) == 0;
}

//=============================================================================
template <typename T>
bool IsFinite (T value)
{
    static_assert(Meta::IsFloat<T>::value, "IsFinite only works with floats");
    return ::isfinite(value);
}

} // namespace Math