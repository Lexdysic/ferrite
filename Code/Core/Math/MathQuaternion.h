//==================================================================================================
//
// File:    MathQuaternion.h
// Author:  Jason Jackson
// Date:    September 20, 2008
//
// Defines a four dimentional complex number
//
//==================================================================================================

#ifdef MATHQUATERNION_H
#  error "Cannot include header more than once."
#endif
#define MATHQUATERNION_H



//*****************************************************************************
//
// Quaternion
//
//*****************************************************************************

class Quaternion
{
public: // Construction
    inline Quaternion ();
    inline Quaternion (float32 a, float32 b, float32 c, float32 d);
    inline Quaternion (const Vector4 & v);
    inline Quaternion (float32 a, const Vector3 & bcd);
    inline Quaternion (const Vector3 & axis, Radian angle);
    Quaternion (const Matrix33 & m);
    Quaternion (const Matrix34 & m);
    Quaternion (const Matrix44 & m);

public: // Operators

    inline Quaternion & operator/= (float32 rhs);
    inline Quaternion & operator*= (float32 rhs);

public: // Data

    union
    {
        struct { float32 a, b, c, d; };
        struct { float32 a; Vector3 v; };
        struct { Vector4 abcd; };
    };
};



//*****************************************************************************
//
// Operators
//
//*****************************************************************************

inline Quaternion operator+ (const Quaternion & lhs, const Quaternion & rhs);
inline Quaternion operator- (const Quaternion & lhs, const Quaternion & rhs);
inline Quaternion operator/ (const Quaternion & lhs, float32 rhs);
inline Quaternion operator* (const Quaternion & lhs, float32 rhs);
inline Quaternion operator* (float32 lhs, const Quaternion & rhs);
inline Quaternion operator* (const Quaternion & lhs, const Quaternion & rhs);
inline Quaternion operator- (const Quaternion & q);
inline Vector3    operator* (const Quaternion & lhs, const Vector3 & rhs);
inline Vector4    operator* (const Quaternion & lhs, const Vector4 & rhs);
inline Vector3    operator* (const Vector3 & lhs, const Quaternion & rhs);
inline Vector4    operator* (const Vector4 & lhs, const Quaternion & rhs);

inline float32    Dot (const Quaternion & lhs, const Quaternion & rhs);
inline float32    Length (const Quaternion & q);
inline float32    LengthSq (const Quaternion & q);
inline Quaternion Normalize (const Quaternion & q);
inline float32    Normalize2 (Quaternion & q);
inline Quaternion Conjugate (const Quaternion & q);
inline Quaternion Inverse (const Quaternion & q);
inline Quaternion Pow (const Quaternion & q, float32 t);
Quaternion        Exp (const Quaternion & q);
Quaternion        Ln (const Quaternion & q);
Quaternion        Slerp (const Quaternion & a, const Quaternion & b, float32 tween);
