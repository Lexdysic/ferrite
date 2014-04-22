//==================================================================================================
//
// File:    MathMatrix.cpp
// Author:  Jason Jackson
// Date:    September 20, 2008
//
// Defines square matrices of different sizes
//
//==================================================================================================

#include "MathPch.h"

//=============================================================================
//
// Matrix22
//
//=============================================================================

//=============================================================================
const Matrix22 Matrix22::Identity(
    1.0f, 0.0f,
    0.0f, 1.0f
);

//=============================================================================
const Matrix22 Matrix22::Zero(
    Vector2::Zero,
    Vector2::Zero
);

//=============================================================================
Matrix22::Matrix22 ()
{
}

//=============================================================================
Matrix22::Matrix22 (const Matrix22 & m) :
    m00(m.m00), m01(m.m01),
    m10(m.m10), m11(m.m11)
{
}

//=============================================================================
Matrix22::Matrix22 (
    const Vector2 & row0,
    const Vector2 & row1
) :
    r0(row0),
    r1(row1)
{
}

//=============================================================================
Matrix22::Matrix22( 
    float32 m00, float32 m01, 
    float32 m10, float32 m11
) :
    r0(m00, m01),
    r1(m10, m11)
{
}

//=============================================================================
Matrix22 Matrix22::CreateRotation (Radian angle)
{
    const float32 cos = Cos(angle);
    const float32 sin = Sin(angle);

    return Matrix22(
        cos, -sin,
        sin, cos
    );
}

//=============================================================================
Matrix22 Matrix22::CreateScale (float32 scale)
{
    return Matrix22(
        scale, 0.0f,
        0.0f, scale
    );
}


//=============================================================================
//
// Matrix23
//
//=============================================================================

//=============================================================================
const Matrix23 Matrix23::Identity(
    1.0f, 0.0f, 0.0f,
    0.0f, 1.0f, 0.0f
);

//=============================================================================
const Matrix23 Matrix23::Zero(
    Vector3::Zero,
    Vector3::Zero
);

//=============================================================================
Matrix23::Matrix23()
{
}

//=============================================================================
Matrix23::Matrix23 (const Matrix23 & m) :
    m00(m.m00), m01(m.m01),
    m10(m.m10), m11(m.m11)
{
}

//=============================================================================
Matrix23::Matrix23 (const Vector3 & row0, const Vector3 & row1) :
    r0(row0),
    r1(row1)
{
}

//=============================================================================
Matrix23::Matrix23( 
    float32 m00, float32 m01, float32 m02,
    float32 m10, float32 m11, float32 m12
) :
    r0(m00, m01, m02),
    r1(m10, m11, m12)
{
}

//=============================================================================
Matrix23 Matrix23::CreateRotation (Radian angle)
{
    const float32 cos = Cos(angle);
    const float32 sin = Sin(angle);

    return Matrix23(
        cos, -sin, 0.0f,
        sin, cos, 0.0f
    );
}

//=============================================================================
Matrix23 Matrix23::CreateScale (float32 scale)
{
    return Matrix23(
        scale, 0.0f, 0.0f,
        0.0f, scale, 0.0f
    );
}

//=============================================================================
Matrix23 Matrix23::CreateTranslation (const Vector2 & v)
{
    return Matrix23(
        1.0f, 0.0f, v.x,
        0.0f, 1.0f, v.y
    );
}

//=============================================================================
Matrix23 Matrix23::CreateTranslation (const Point2 & p)
{
    return Matrix23(
        1.0f, 0.0f, p.x,
        0.0f, 1.0f, p.y
    );
}

//=============================================================================
Matrix23 Matrix23::CreateTransform (const Point2 & position, Radian rotation)
{
    const float32 cos = Cos(rotation);
    const float32 sin = Sin(rotation);

    return Matrix23(
        cos, -sin, position.x,
        sin, cos, position.y
    );
}

//=============================================================================
//
// Matrix33
//
//=============================================================================

//=============================================================================
const Matrix33 Matrix33::Identity(
    1.0f, 0.0f, 0.0f,
    0.0f, 1.0f, 0.0f,
    0.0f, 0.0f, 1.0f
);

//=============================================================================
const Matrix33 Matrix33::Zero(
    Vector3::Zero,
    Vector3::Zero,
    Vector3::Zero
);

//=============================================================================
Matrix33::Matrix33 ()
{
}

//=============================================================================
Matrix33::Matrix33 (const Matrix33 & m) :
    r0(m.r0),
    r1(m.r1),
    r2(m.r2)
{
}

//=============================================================================
Matrix33::Matrix33 (
    const Vector3 & r0,
    const Vector3 & r1,
    const Vector3 & r2
) :
    r0(r0),
    r1(r1),
    r2(r2)
{
}

//=============================================================================
Matrix33::Matrix33( 
    float32 m00, float32 m01, float32 m02,
    float32 m10, float32 m11, float32 m12,
    float32 m20, float32 m21, float32 m22
) :
    r0(m00, m01, m02),
    r1(m10, m11, m12),
    r2(m20, m21, m22)
{
}

//=============================================================================
Matrix33::Matrix33( const Quaternion & q )
{
    const float32 xx = 2.0f * q.v.x * q.v.x;
    const float32 yy = 2.0f * q.v.y * q.v.y;
    const float32 zz = 2.0f * q.v.z * q.v.z;
    const float32 xy = 2.0f * q.v.x * q.v.y;
    const float32 xz = 2.0f * q.v.x * q.v.z;
    const float32 yz = 2.0f * q.v.y * q.v.z;

    const float32 xw = 2.0f * q.v.x * q.a;
    const float32 yw = 2.0f * q.v.y * q.a;
    const float32 zw = 2.0f * q.v.z * q.a;

    mv[0] = Vector3( 1.0f - yy - zz,           xy - zw,            xz + yw );
    mv[1] = Vector3(        xy + zw,    1.0f - xx - zz,            yz - xw );
    mv[2] = Vector3(        xz - yw,           yz + xw,     1.0f - xx - yy );
}


//=============================================================================
//
// Matrix34
//
//=============================================================================

//=============================================================================
const Matrix34 Matrix34::Identity(
    1.0f, 0.0f, 0.0f, 0.0f,
    0.0f, 1.0f, 0.0f, 0.0f,
    0.0f, 0.0f, 1.0f, 0.0f
);

//=============================================================================
const Matrix34 Matrix34::Zero(
    Vector4::Zero,
    Vector4::Zero,
    Vector4::Zero
);

//=============================================================================
Matrix34::Matrix34 ()
{
}

//=============================================================================
Matrix34::Matrix34 (const Matrix34 & m) :
    r0(m.r0),
    r1(m.r1),
    r2(m.r2)
{
}

//=============================================================================
Matrix34::Matrix34 (
    const Vector4 & r0,
    const Vector4 & r1,
    const Vector4 & r2
) :
    r0(r0),
    r1(r1),
    r2(r2)
{
}

//=============================================================================
Matrix34::Matrix34(
    float32 m00, float32 m01, float32 m02, float32 m03,
    float32 m10, float32 m11, float32 m12, float32 m13,
    float32 m20, float32 m21, float32 m22, float32 m23
) :
    r0(m00, m01, m02, m03),
    r1(m10, m11, m12, m13),
    r2(m20, m21, m22, m23)
{
}

//=============================================================================
Matrix34::Matrix34 (const Matrix33 & m, const Vector3 & t) :
    r0(m.r0, t.x),
    r1(m.r1, t.y),
    r2(m.r2, t.z)
{
}

//=============================================================================
Matrix34::Matrix34 (const Quaternion & q)
{
    const float32 xx = 2.0f * q.v.x * q.v.x;
    const float32 yy = 2.0f * q.v.y * q.v.y;
    const float32 zz = 2.0f * q.v.z * q.v.z;
    const float32 xy = 2.0f * q.v.x * q.v.y;
    const float32 xz = 2.0f * q.v.x * q.v.z;
    const float32 yz = 2.0f * q.v.y * q.v.z;

    const float32 xw = 2.0f * q.v.x * q.a;
    const float32 yw = 2.0f * q.v.y * q.a;
    const float32 zw = 2.0f * q.v.z * q.a;

    mv[0] = Vector4( 1.0f - yy - zz,           xy - zw,            xz + yw,     0.0f );
    mv[1] = Vector4(        xy + zw,    1.0f - xx - zz,            yz - xw,     0.0f );
    mv[2] = Vector4(        xz - yw,           yz + xw,     1.0f - xx - yy,     0.0f );
}

//=============================================================================
Matrix34::Matrix34 (const Quaternion & q, const Vector3 & t)
{
    const float32 xx = 2.0f * q.v.x * q.v.x;
    const float32 yy = 2.0f * q.v.y * q.v.y;
    const float32 zz = 2.0f * q.v.z * q.v.z;
    const float32 xy = 2.0f * q.v.x * q.v.y;
    const float32 xz = 2.0f * q.v.x * q.v.z;
    const float32 yz = 2.0f * q.v.y * q.v.z;

    const float32 xw = 2.0f * q.v.x * q.a;
    const float32 yw = 2.0f * q.v.y * q.a;
    const float32 zw = 2.0f * q.v.z * q.a;

    mv[0] = Vector4( 1.0f - yy - zz,           xy - zw,            xz + yw,     t.x );
    mv[1] = Vector4(        xy + zw,    1.0f - xx - zz,            yz - xw,     t.y );
    mv[2] = Vector4(        xz - yw,           yz + xw,     1.0f - xx - yy,     t.z );  
}

//----------------------------------------------------------------------------------------------------//

//=============================================================================
//
// Matrix44
//
//=============================================================================

//=============================================================================
const Matrix44 Matrix44::Identity(
    1.0f, 0.0f, 0.0f, 0.0f,
    0.0f, 1.0f, 0.0f, 0.0f,
    0.0f, 0.0f, 1.0f, 0.0f,
    0.0f, 0.0f, 0.0f, 1.0f
);

//=============================================================================
const Matrix44 Matrix44::Zero(
    Vector4::Zero,
    Vector4::Zero,
    Vector4::Zero,
    Vector4::Zero
);

//=============================================================================
Matrix44::Matrix44 ()
{
}

//=============================================================================
Matrix44::Matrix44 (const Matrix44 & m)
{
    m;
    ASSERT( !"Not Implemented" );
}

//=============================================================================
Matrix44::Matrix44 ( 
    const Vector4 & r0,
    const Vector4 & r1,
    const Vector4 & r2,
    const Vector4 & r3
) :
    r0(r0),
    r1(r1),
    r2(r2),
    r3(r3)
{
}

//=============================================================================
Matrix44::Matrix44 (
    float32 m00, float32 m01, float32 m02, float32 m03,
    float32 m10, float32 m11, float32 m12, float32 m13,
    float32 m20, float32 m21, float32 m22, float32 m23,
    float32 m30, float32 m31, float32 m32, float32 m33
) :
    r0(m00, m01, m02, m03),
    r1(m10, m11, m12, m13),
    r2(m20, m21, m22, m23),
    r3(m30, m31, m32, m33)
{
}

//=============================================================================
Matrix44::Matrix44 (const Quaternion & q)
{
    const float32 xx = 2.0f * q.v.x * q.v.x;
    const float32 yy = 2.0f * q.v.y * q.v.y;
    const float32 xy = 2.0f * q.v.x * q.v.y;

    const float32 xz = 2.0f * q.v.x * q.v.z;
    const float32 yz = 2.0f * q.v.y * q.v.z;
    const float32 zz = 2.0f * q.v.z * q.v.z;

    const float32 xw = 2.0f * q.v.x * q.a;
    const float32 yw = 2.0f * q.v.y * q.a;
    const float32 zw = 2.0f * q.v.z * q.a;

    mv[0] = Vector4( 1.0f - yy - zz,           xy - zw,            xz + yw,     0.0f );
    mv[1] = Vector4(        xy + zw,    1.0f - xx - zz,            yz - xw,     0.0f);
    mv[2] = Vector4(        xz - yw,           yz + xw,     1.0f - xx - yy,     0.0f ); 
    mv[3] = Vector4(           0.0f,              0.0f,               0.0f,     1.0f );
}

//=============================================================================
Matrix44::Matrix44 (const Quaternion & q, const Vector3 & t)
{
    const float32 xx = 2.0f * q.v.x * q.v.x;
    const float32 yy = 2.0f * q.v.y * q.v.y;
    const float32 zz = 2.0f * q.v.z * q.v.z;
    const float32 xy = 2.0f * q.v.x * q.v.y;
    const float32 xz = 2.0f * q.v.x * q.v.z;
    const float32 yz = 2.0f * q.v.y * q.v.z;
    const float32 xw = 2.0f * q.v.x * q.a;
    const float32 yw = 2.0f * q.v.y * q.a;
    const float32 zw = 2.0f * q.v.z * q.a;

    mv[0] = Vector4( 1.0f - yy - zz,           xy - zw,            xz + yw,     t.x );
    mv[1] = Vector4(        xy + zw,    1.0f - xx - zz,            yz - xw,     t.y );
    mv[2] = Vector4(        xz - yw,           yz + xw,     1.0f - xx - yy,     t.z );  
    mv[3] = Vector4(           0.0f,              0.0f,               0.0f,     1.0f );
}

//----------------------------------------------------------------------------------------------------//

const float32 & Matrix22::operator()( uint32 r, uint32 c ) const          { return mv[r][c]; }
const float32 & Matrix33::operator()( uint32 r, uint32 c ) const          { return mv[r][c]; }
const float32 & Matrix34::operator()( uint32 r, uint32 c ) const          { return mv[r][c]; }
const float32 & Matrix44::operator()( uint32 r, uint32 c ) const          { return mv[r][c]; }

//----------------------------------------------------------------------------------------------------//

float32 & Matrix22::operator()( uint32 r, uint32 c )                      { return mv[r][c]; }
float32 & Matrix33::operator()( uint32 r, uint32 c )                      { return mv[r][c]; }
float32 & Matrix34::operator()( uint32 r, uint32 c )                      { return mv[r][c]; }
float32 & Matrix44::operator()( uint32 r, uint32 c )                      { return mv[r][c]; }


