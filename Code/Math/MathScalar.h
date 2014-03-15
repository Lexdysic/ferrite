//==================================================================================================
//
// File:    MathScalar.h
// Author:  Jason Jackson
// Date:    September 20, 2008
//
// Defines basic math operations dealing with scalars
//
//==================================================================================================

#ifdef MATHSCALAR_H
#  error "Cannot include header more than once."
#endif
#define MATHSCALAR_H

template <typename T>
inline T Sign (const T & x);

template <typename T>
inline T Sq(const T & x);

template <typename Float>
inline Float Sqrt (Float x);

inline float32 Cos (Radian x);
inline float32 Sin (Radian x);
inline float32 Tan (Radian x);
inline Radian  ArcSin (float32 a);
inline Radian  ArcCos (float32 a);
inline Radian  ArcTan (float32 a);
inline Radian  ArcTan (float32 x, float32 y);

template <typename Float>
inline Float Floor(Float x);

template <typename Float>
inline Float Ceil (Float x);

template <typename Float>
inline Float Frac (Float x);

template <typename T>
inline T Abs (T x);

inline float32 Pow (float32 b, float32 e);
inline float32 Exp (float32 x);

inline float32 Log (float32 x);
inline float32 Ln (float32 x);
inline float32 Lg (float32 x);
inline float32 Log (float32 x, float32 base);

inline float32 Mod (float32 x, float32 divisor);
inline float32 Difference (float32 a, float32 b, float32 modulo);

inline float32 Inverse (float32 x);
inline float64 Inverse (float64 x);

bool           Equal (float32 a, float32 b, sint maxUlps = Math::MaxUlps);

inline sint    FloatToSint (float32 x);
inline sint    FloatToSint (float64 x);
inline uint    FloatToUint (float32 x);
inline uint    FloatToUint (float64 x);
inline sint64  FloatToSint64 (float32 x);
inline sint64  FloatToSint64 (float64 x);


#undef min
#undef max
template <typename T, typename... Ts>
inline T Min (const T & a, const T & b, const Ts &... args);

template <typename T, typename... Ts>
inline T Max (const T & a, const T & b, const Ts &... args);

template <typename T>
inline T Clamp (const T & x, const T & min, const T & max);


template <typename T>
inline T Lerp (const T & a, const T & b, float32 t);
template <typename T>
inline float32 InvLerp (const T & x, const T & a, const T & b);




namespace Math
{

inline uint BitCount (uint32 n);

template <typename T>
inline bool IsInRange (const T & x, const T & a, const T & b);

template <typename T>
inline T Map (const T & inMin, const T & inMax, const T & outMin, const T & outMax, const T & input);

template <typename T>
inline T MapClamp (const T & inMin, const T & inMax, const T & outMin, const T & outMax, const T & input);

template <typename T>
inline bool IsPowerTwo (T value);

} // namespace Math


