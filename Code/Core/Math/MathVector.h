//==================================================================================================
//
// File:    MathVector.h
// Author:  Jason Jackson
// Date:    September 20, 2008
//
// Definition of vectors in 2-, 3-, and 4-Space and their operators
//
//==================================================================================================

#ifdef MATHVECTOR_H
#  error "Cannot include header more than once."
#endif
#define MATHVECTOR_H


//=============================================================================
//
// Represents a 2-dimensional vector
//
//=============================================================================

class Vector2
{
public:
    inline Vector2 ();
    inline Vector2 (const Vector2 & v);
    inline Vector2 (float32 c1, float32 c2);
    
    inline Vector2 &    operator=  (const Vector2 & v);

    inline Vector2 &    operator*= (float32 s);
    inline Vector2 &    operator/= (float32 s);
    inline Vector2 &    operator*= (const Vector2 & v);
    inline Vector2 &    operator/= (const Vector2 & v);
    inline Vector2 &    operator+= (const Vector2 & v);
    inline Vector2 &    operator-= (const Vector2 & v);

    inline const float32 &  operator[] (uint32 i) const;
    inline       float32 &  operator[] (uint32 i);

    static const Vector2 Zero;
    static const Vector2 One;
    static const Vector2 UnitX;
    static const Vector2 UnitY;
    static const Vector2 Infinity;

    union { 
        struct { float32 x, y; };
        //struct { float32 u, v; };
    };

};


//=============================================================================
//
// Represents a 3-dimensional vector
//
//=============================================================================

class Vector3
{
public:
    inline Vector3();
    inline Vector3( const Vector3 & v );
    inline explicit Vector3( const Vector2 & c12, float32 c3 );
    inline explicit Vector3( float32 c1, const Vector2 & c23 );
    inline Vector3( float32 c1, float32 c2, float32 c3 );

    inline Vector3 &    operator=( const Vector3 & v );
    inline Vector3 &    operator/=( const Vector3 & v );
    inline Vector3 &    operator/=( float32 s );
    inline Vector3 &    operator*=( const Vector3 & v );
    inline Vector3 &    operator*=( float32 s );
    inline Vector3 &    operator+=( const Vector3 & v );
    inline Vector3 &    operator-=( const Vector3 & v );
    inline const float32 &  operator[] (uint32 i) const;
    inline       float32 &  operator[] (uint32 i);


    static const Vector3 Zero;
    static const Vector3 One;
    static const Vector3 UnitX;
    static const Vector3 UnitY;
    static const Vector3 UnitZ;
    static const Vector3 Infinity;


    union
    {
        struct { float32 x,     y,      z; };
        //struct { float32 u,     v,      w; };
        //struct { float32 i,     j,      k; };
        //struct { Vector2 xy;           float32 z; };
        //struct { float32 x;           Vector2 yz; };
    };
};


//=============================================================================
//
// Represents a 4-dimensional vector
//
//=============================================================================

class Vector4
{
public:
    inline Vector4();
    inline Vector4( const p3 & p );
    inline Vector4( const Vector3 & v );
    inline Vector4( const Vector4 & v );
    inline Vector4( const q32 & q );
    inline Vector4( const Vector3 & c123, float32 c4 );
    inline Vector4( float32 c1, const Vector3 & c234 );
    inline Vector4( const Vector2 & c12, const Vector2 & c34 );
    inline Vector4( float32 c1, const Vector2 & c23, float32 c4 );
    inline Vector4( float32 c1, float32 c2, float32 c3, float32 c4 );

    inline Vector4 &    operator=( const Vector4 & v );
    inline Vector4 &    operator/=( const Vector4 & v );
    inline Vector4 &    operator/=( float32 s );
    inline Vector4 &    operator*=( const Vector4 & v );
    inline Vector4 &    operator*=( float32 s );
    inline Vector4 &    operator+=( const Vector4 & v );
    inline Vector4 &    operator-=( const Vector4 & v );
    inline const float32 &  operator[]( uint32 i ) const;
    inline       float32 &  operator[]( uint32 i );

    static const Vector4 Zero;
    static const Vector4 One;
    static const Vector4 UnitX;
    static const Vector4 UnitY;
    static const Vector4 UnitZ;
    static const Vector4 UnitW;
    static const Vector4 Infinity;

    union
    {
        struct { float32 x, y, z, w; };
        //struct { float32 u, v; };
        struct { Vector2 uv; };
        struct { Vector3 uvw; };
        struct { Vector3 xyz; };
        struct { float32 x; Vector2 yz; };
        struct { float32 x; Vector3 yzw; };
        struct { Vector2 xy, zw; };
    };
};


//=============================================================================
//
// Operators
//
//=============================================================================

inline Vector2   operator+( const Vector2 & lhs,  const Vector2 & rhs );
inline Vector3   operator+( const Vector3 & lhs,  const Vector3 & rhs );
inline Vector4   operator+( const Vector4 & lhs,  const Vector4 & rhs );

inline Vector2   operator-( const Vector2 & lhs,  const Vector2 & rhs );
inline Vector3   operator-( const Vector3 & lhs,  const Vector3 & rhs );
inline Vector4   operator-( const Vector4 & lhs,  const Vector4 & rhs );

inline Vector2   operator*( const float32 & lhs, const Vector2 & rhs );
inline Vector3   operator*( const float32 & lhs, const Vector3 & rhs );
inline Vector4   operator*( const float32 & lhs, const Vector4 & rhs );

inline Vector2   operator*( const Vector2 & rhs,  const float32 & lhs );
inline Vector3   operator*( const Vector3 & rhs,  const float32 & lhs );
inline Vector4   operator*( const Vector4 & rhs,  const float32 & lhs );

inline Vector2   operator*( const Vector2 & lhs,  const Vector2 & rhs );
inline Vector3   operator*( const Vector3 & lhs,  const Vector3 & rhs );
inline Vector4   operator*( const Vector4 & lhs,  const Vector4 & rhs );

inline Vector2   operator/( const Vector2 & lhs,  const Vector2 & rhs );
inline Vector3   operator/( const Vector3 & lhs,  const Vector3 & rhs );
inline Vector4   operator/( const Vector4 & lhs,  const Vector4 & rhs );

inline Vector2   operator/( const Vector2 & rhs,  const float32 & lhs );
inline Vector3   operator/( const Vector3 & rhs,  const float32 & lhs );
inline Vector4   operator/( const Vector4 & rhs,  const float32 & lhs );

inline Vector2   operator-( const Vector2 & v );
inline Vector3   operator-( const Vector3 & v );
inline Vector4   operator-( const Vector4 & v );

inline bool operator==( const Vector2 & lhs, const Vector2 & rhs );
inline bool operator==( const Vector3 & lhs, const Vector3 & rhs );
inline bool operator==( const Vector4 & lhs, const Vector4 & rhs );

inline bool operator!=( const Vector2 & lhs, const Vector2 & rhs );
inline bool operator!=( const Vector3 & lhs, const Vector3 & rhs );
inline bool operator!=( const Vector4 & lhs, const Vector4 & rhs );

inline float32  Dot( const Vector2 & lhs, const Vector2 & rhs );
inline float32  Dot( const Vector3 & lhs, const Vector3 & rhs );
inline float32  Dot( const Vector4 & lhs, const Vector4 & rhs );

inline float32 Cross (const Vector2 & lhs, const Vector2 & rhs);
inline Vector3 Cross (const Vector3 & lhs, const Vector3 & rhs);

inline Vector2 Perpendicular (const Vector2 & v);

inline Matrix22  Tensor (const Vector2 & lhs, const Vector2 & rhs);
inline Matrix33  Tensor (const Vector3 & lhs, const Vector3 & rhs);

inline Vector2 Sq (const Vector2 & v);
inline Vector3 Sq (const Vector3 & v);

inline Vector2   Normalize (const Vector2 & v);
inline Vector3   Normalize (const Vector3 & v);
inline Vector4   Normalize (const Vector4 & v);

inline Vector2   Normalize (const Vector2 & v, float32 * outLength);
inline Vector3   Normalize (const Vector3 & v, float32 * outLength);
inline Vector4   Normalize (const Vector4 & v, float32 * outLength);

// TODO (jason): want a better name for this
inline float32  Normalize2( Vector2 & v );
inline float32  Normalize2( Vector3 & v );
inline float32  Normalize2( Vector4 & v );

inline float32  Length( const Vector2 & v );
inline float32  Length( const Vector3 & v );
inline float32  Length( const Vector4 & v );

inline float32  LengthSq (const Vector2 & v);
inline float32  LengthSq (const Vector3 & v);
inline float32  LengthSq (const Vector4 & v);

inline bool IsParallel (const Vector2 & a, const Vector2 & b);
inline bool IsParallel (const Vector3 & a, const Vector3 & b);
inline bool IsParallel (const Vector4 & a, const Vector4 & b);

inline bool IsPerpendicular (const Vector2 & a, const Vector2 & b);
inline bool IsPerpendicular (const Vector3 & a, const Vector3 & b);
inline bool IsPerpendicular (const Vector4 & a, const Vector4 & b);

inline Vector2 Mirror (const Vector2 & a, const Vector2 & n);
inline Vector3 Mirror (const Vector3 & a, const Vector3 & n);

inline float32 Min (const Vector2 & v);
inline float32 Min (const Vector3 & v);
inline float32 Min (const Vector4 & v);

inline Vector2 Min (const Vector2 & a, const Vector2 & b);
inline Vector3 Min (const Vector3 & a, const Vector3 & b);
inline Vector4 Min (const Vector4 & a, const Vector4 & b);

inline float32 Max (const Vector2 & v);
inline float32 Max (const Vector3 & v);
inline float32 Max (const Vector4 & v);

inline Vector2 Max (const Vector2 & a, const Vector2 & b);
inline Vector3 Max (const Vector3 & a, const Vector3 & b);
inline Vector4 Max (const Vector4 & a, const Vector4 & b);

inline Vector2 Abs (const Vector2 & v);
inline Vector3 Abs (const Vector3 & v);
inline Vector4 Abs (const Vector4 & v);

inline Vector2 Sign (const Vector2 & v);
inline Vector3 Sign (const Vector3 & v);
inline Vector4 Sign (const Vector4 & v);

inline bool Equal (const Vector2 & a, const Vector2 & b, sint32 maxUlps = Math::MaxUlps);
inline bool Equal (const Vector3 & a, const Vector3 & b, sint32 maxUlps = Math::MaxUlps);
inline bool Equal (const Vector4 & a, const Vector4 & b, sint32 maxUlps = Math::MaxUlps);

inline bool Normalized (const Vector2 & v, sint32 maxUlps = Math::MaxUlps);
inline bool Normalized (const Vector3 & v, sint32 maxUlps = Math::MaxUlps);
inline bool Normalized (const Vector4 & v, sint32 maxUlps = Math::MaxUlps);

void BuildBasis (const Vector3 & x, Vector3 & u, Vector3 & v, Vector3 & w);


