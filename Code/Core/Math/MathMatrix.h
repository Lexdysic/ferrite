//==================================================================================================
//
// File:    MathMatrix.h
// Author:  Jason Jackson
// Date:    September 20, 2008
//
// Defines square matrices of different sizes
//
//==================================================================================================

#ifdef MATHMATRIX_H
#  error "Cannot include header more than once."
#endif
#define MATHMATRIX_H


//=============================================================================
//
// Matrix22
//
//=============================================================================

class Matrix22
{
public:
    Matrix22 ();
    Matrix22 (const Matrix22 & m);
    Matrix22 (
        const Vector2 & row0,
        const Vector2 & row1
    );
    Matrix22 (
        float32 m00, float32 m01,
        float32 m10, float32 m11
    );

    static Matrix22 CreateRotation (Radian angle);
    static Matrix22 CreateScale (float32 scale);

    const float32 &         operator() (uint32 r, uint32 c) const;
          float32 &         operator() (uint32 r, uint32 c);

    inline const Vector2 & Row (uint32 r) const;
    inline Vector2         Column (uint32 c) const;

    static const Matrix22 Identity;
    static const Matrix22 Zero;

    union
    {
        struct {
            float32 m00, m01;
            float32 m10, m11;
        };
        struct { Vector2 mv[2]; };
        struct { Vector2 r0, r1; };
        float32 ma[2*2];
    };
};



//=============================================================================
//
// Matrix23 - The3rd row is implictly [0, 0, 1].
//
//=============================================================================

class Matrix23
{
public: // Construction
    Matrix23 ();
    Matrix23 (const Matrix23 & m);
    Matrix23 (
        const Vector3 & row0,
        const Vector3 & row1
    );
    Matrix23 (
        float32 _00, float32 _01, float32 _02, 
        float32 _10, float32 _11, float32 _12
   );

    static Matrix23 CreateRotation (Radian angle);
    static Matrix23 CreateScale (float32 scale);
    static Matrix23 CreateScale (const Vector2 & scale);
    static Matrix23 CreateTranslation (const Vector2 & v);
    static Matrix23 CreateTranslation (const Point2 & position);
    static Matrix23 CreateTransform (const Point2 & position, Radian rotation);

    // Accessors
    const float32 &         operator() (uint32 r, uint32 c) const;
          float32 &         operator() (uint32 r, uint32 c);

    inline const Vector3 & Row (uint32 r) const;
    inline Vector2         Column (uint32 c) const;


    static const Matrix23 Identity;
    static const Matrix23 Zero;



    union
    {
        struct {
            float32 m00, m01, m02;
            float32 m10, m11, m12;
        };
        struct { Vector3 mv[2]; };
        struct { Vector3 r0, r1; };
        float32 ma[2*3];
    };
};



//=============================================================================
//
// Matrix33
//
//=============================================================================

class Matrix33
{
public:
    Matrix33 ();
    Matrix33 (const Matrix33 & m);
    Matrix33 (
        const Vector3 & r1,
        const Vector3 & r2,
        const Vector3 & r3
    );
    Matrix33 (
        float32 e00, float32 e01, float32 e02,
        float32 e10, float32 e11, float32 e12,
        float32 e20, float32 e21, float32 e22
    );
    Matrix33 (const Quaternion & q);

    const float32 &         operator() (uint32 r, uint32 c) const;
          float32 &         operator() (uint32 r, uint32 c);

    inline const Vector3 & Row (uint32 r) const;
    inline Vector3         Column (uint32 c) const;

    static const Matrix33 Identity;
    static const Matrix33 Zero;

    union
    {
        struct {
            float32 m00, m01, m02;
            float32 m10, m11, m12;
            float32 m20, m21, m22;
        };
        struct { Vector3 mv[3]; };
        struct { Vector3 r0, r1, r2; };
        float32 ma[3*3];
    };

};

//=============================================================================
//
// Matrix34 - The 4th row is implictly [0, 0, 0, 1].
//
//=============================================================================

class Matrix34
{
public:
    Matrix34 ();
    Matrix34 (const Matrix34 & m);
    Matrix34 (
        const Vector4 & r0,
        const Vector4 & r1,
        const Vector4 & r2
    );
    Matrix34 (
        float32 m00, float32 m01, float32 m02, float32 m03,
        float32 m10, float32 m11, float32 m12, float32 m13,
        float32 m20, float32 m21, float32 m22, float32 m23
    );
    Matrix34 (const Matrix33 & m, const Vector3 & t);
    Matrix34 (const Quaternion & q);
    Matrix34 (const Quaternion & q, const Vector3 & t);

    const float32 &         operator() (uint32 r, uint32 c) const;
          float32 &         operator() (uint32 r, uint32 c);

    inline const Vector4 & Row (uint32 r) const;
    inline Vector3         Column (uint32 c) const;


    static const Matrix34 Identity;
    static const Matrix34 Zero;

    union
    {
        struct {
            float32 m00, m01, m02, m03;
            float32 m10, m11, m12, m13;
            float32 m20, m21, m22, m23;
        };
        struct { Vector4 mv[3]; };
        struct { Vector4 r0, r1, r2; };
        float32 ma[3*4];
    };
};



//=============================================================================
//
// Matrix44
//
//=============================================================================

class Matrix44
{
public:
    Matrix44 ();
    Matrix44 (const Matrix44 & m);
    Matrix44 (
        const Vector4 & r0,
        const Vector4 & r1,
        const Vector4 & r2,
        const Vector4 & r3
    );
    Matrix44 (
        float32 m00, float32 m01, float32 m02, float32 m03,
        float32 m10, float32 m11, float32 m12, float32 m13,
        float32 m20, float32 m21, float32 m22, float32 m23,
        float32 m30, float32 m31, float32 m32, float32 m33
    );
    Matrix44 (const Quaternion & q);
    Matrix44 (const Quaternion & q, const Vector3 & t);


    const float32 & operator() (uint32 r, uint32 c) const;
          float32 & operator() (uint32 r, uint32 c);

    inline const Vector4 & Row (uint32 r) const;
    inline Vector4         Column (uint32 c) const;


    static const Matrix44 Identity;
    static const Matrix44 Zero;

    union
    {
        struct {
            float32 m00, m01, m02, m03;
            float32 m10, m11, m12, m13;
            float32 m20, m21, m22, m23;
            float32 m30, m31, m32, m33;
        };
        struct { Vector4 mv[4]; };
        struct { Vector4 r0, r1, r2, r3; };
        float32 ma[4*4];
    };
};



//=============================================================================
//
// Operators
//
//=============================================================================

inline Matrix22 operator+ (const Matrix22 & lhs, const Matrix22 & rhs);
inline Matrix33 operator+ (const Matrix33 & lhs, const Matrix33 & rhs);
inline Matrix34 operator+ (const Matrix34 & lhs, const Matrix34 & rhs);
inline Matrix44 operator+ (const Matrix44 & lhs, const Matrix44 & rhs);

inline Matrix22 operator- (const Matrix22 & lhs, const Matrix22 & rhs);
inline Matrix33 operator- (const Matrix33 & lhs, const Matrix33 & rhs);
inline Matrix34 operator- (const Matrix34 & lhs, const Matrix34 & rhs);
inline Matrix44 operator- (const Matrix44 & lhs, const Matrix44 & rhs);

inline Matrix22 operator* (const Matrix22 & lhs, const Matrix22 & rhs);
inline Matrix23 operator* (const Matrix23 & lhs, const Matrix23 & rhs);
inline Matrix33 operator* (const Matrix33 & lhs, const Matrix33 & rhs);
inline Matrix34 operator* (const Matrix34 & lhs, const Matrix34 & rhs);
inline Matrix44 operator* (const Matrix44 & lhs, const Matrix44 & rhs);

inline Matrix22 operator* (const Matrix22 & lhs, const float32 & rhs);
inline Matrix23 operator* (const Matrix23 & lhs, const float32 & rhs);
inline Matrix33 operator* (const Matrix33 & lhs, const float32 & rhs);
inline Matrix34 operator* (const Matrix34 & lhs, const float32 & rhs);
inline Matrix44 operator* (const Matrix44 & lhs, const float32 & rhs);

inline Matrix22 operator* (const float32 & rhs, const Matrix22 & lhs);
inline Matrix33 operator* (const float32 & rhs, const Matrix33 & lhs);
inline Matrix34 operator* (const float32 & rhs, const Matrix34 & lhs);
inline Matrix44 operator* (const float32 & rhs, const Matrix44 & lhs);

inline Matrix22 operator/ (const Matrix22 & lhs, const float32 & rhs);
inline Matrix23 operator/ (const Matrix23 & lhs, const float32 & rhs);
inline Matrix33 operator/ (const Matrix33 & lhs, const float32 & rhs);
inline Matrix34 operator/ (const Matrix34 & lhs, const float32 & rhs);
inline Matrix44 operator/ (const Matrix44 & lhs, const float32 & rhs);

inline Vector2 operator* (const Matrix22 & lhs, const Vector2 & rhs);
inline Vector2 operator* (const Matrix23 & lhs, const Vector2 & rhs);
inline Vector3 operator* (const Matrix23 & lhs, const Vector3 & rhs);
inline Vector3 operator* (const Matrix33 & lhs, const Vector3 & rhs);
inline Vector3 operator* (const Matrix34 & lhs, const Vector3 & rhs);
inline Vector3 operator* (const Matrix34 & lhs, const Vector4 & rhs);
inline Vector4 operator* (const Matrix44 & lhs, const Vector4 & rhs);

inline bool operator== (const Matrix22 & lhs, const Matrix22 & rhs);
inline bool operator== (const Matrix33 & lhs, const Matrix33 & rhs);
inline bool operator== (const Matrix34 & lhs, const Matrix34 & rhs);
inline bool operator== (const Matrix44 & lhs, const Matrix44 & rhs);

inline bool operator!= (const Matrix22 & lhs, const Matrix22 & rhs);
inline bool operator!= (const Matrix33 & lhs, const Matrix33 & rhs);
inline bool operator!= (const Matrix34 & lhs, const Matrix34 & rhs);
inline bool operator!= (const Matrix44 & lhs, const Matrix44 & rhs);

inline Matrix22     Transpose (const Matrix22 & m);
inline Matrix33     Transpose (const Matrix33 & m);
inline Matrix34     Transpose (const Matrix34 & m);
inline Matrix44     Transpose (const Matrix44 & m);

inline float32      Trace (const Matrix22 & m);
inline float32      Trace (const Matrix33 & m);
inline float32      Trace (const Matrix34 & m);
inline float32      Trace (const Matrix44 & m);

inline float32      Determinant (const Matrix22 & m);
inline float32      Determinant (const Matrix23 & m);
inline float32      Determinant (const Matrix33 & m);
inline float32      Determinant (const Matrix34 & m);
inline float32      Determinant (const Matrix44 & m);

inline Matrix22     Inverse (const Matrix22 & m);
inline Matrix23     Inverse (const Matrix23 & m);
inline Matrix33     Inverse (const Matrix33 & m);
inline Matrix34     Inverse (const Matrix34 & m);
inline Matrix44     Inverse (const Matrix44 & m);

inline bool         Equal (const Matrix22 & lhs, const Matrix22 & rhs, sint32 maxUlps = Math::MaxUlps);
inline bool         Equal (const Matrix33 & lhs, const Matrix33 & rhs, sint32 maxUlps = Math::MaxUlps);
inline bool         Equal (const Matrix34 & lhs, const Matrix34 & rhs, sint32 maxUlps = Math::MaxUlps);
inline bool         Equal (const Matrix44 & lhs, const Matrix44 & rhs, sint32 maxUlps = Math::MaxUlps);
