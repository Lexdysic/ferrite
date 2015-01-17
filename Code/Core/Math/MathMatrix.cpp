
#include "MathPch.h"


//*****************************************************************************
//
// Matrix22
//
//*****************************************************************************

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
    row0(row0),
    row1(row1)
{
}

//=============================================================================
Matrix22::Matrix22 ( 
    float32 m00, float32 m01, 
    float32 m10, float32 m11
) :
    row0(m00, m01),
    row1(m10, m11)
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



//*****************************************************************************
//
// Matrix23
//
//*****************************************************************************

//=============================================================================
const Matrix23 Matrix23::Identity (
    1.0f, 0.0f, 0.0f,
    0.0f, 1.0f, 0.0f
);

//=============================================================================
const Matrix23 Matrix23::Zero (
    Vector3::Zero,
    Vector3::Zero
);

//=============================================================================
Matrix23::Matrix23 ()
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
    row0(row0),
    row1(row1)
{
}

//=============================================================================
Matrix23::Matrix23 ( 
    float32 m00, float32 m01, float32 m02,
    float32 m10, float32 m11, float32 m12
) :
    row0(m00, m01, m02),
    row1(m10, m11, m12)
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
Matrix23 Matrix23::CreateScale (const Vector2 & scale)
{
    return Matrix23(
        scale.x, 0.0f, 0.0f,
        0.0f, scale.y, 0.0f
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
        sin,  cos, position.y
    );
}



//*****************************************************************************
//
// Matrix33
//
//*****************************************************************************

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
    row0(m.row0),
    row1(m.row1),
    row2(m.row2)
{
}

//=============================================================================
Matrix33::Matrix33 (
    const Vector3 & r0,
    const Vector3 & r1,
    const Vector3 & r2
) :
    row0(r0),
    row1(r1),
    row2(r2)
{
}

//=============================================================================
Matrix33::Matrix33 ( 
    float32 m00, float32 m01, float32 m02,
    float32 m10, float32 m11, float32 m12,
    float32 m20, float32 m21, float32 m22
) :
    row0(m00, m01, m02),
    row1(m10, m11, m12),
    row2(m20, m21, m22)
{
}

//=============================================================================
Matrix33::Matrix33 (const Quaternion & q)
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

    row[0] = Vector3(1.0f - yy - zz,        xy - zw,        xz + yw);
    row[1] = Vector3(       xy + zw, 1.0f - xx - zz,        yz - xw);
    row[2] = Vector3(       xz - yw,        yz + xw, 1.0f - xx - yy);
}



//*****************************************************************************
//
// Matrix34
//
//*****************************************************************************

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
    row0(m.row0),
    row1(m.row1),
    row2(m.row2)
{
}

//=============================================================================
Matrix34::Matrix34 (
    const Vector4 & r0,
    const Vector4 & r1,
    const Vector4 & r2
) :
    row0(row0),
    row1(row1),
    row2(row2)
{
}

//=============================================================================
Matrix34::Matrix34 (
    float32 m00, float32 m01, float32 m02, float32 m03,
    float32 m10, float32 m11, float32 m12, float32 m13,
    float32 m20, float32 m21, float32 m22, float32 m23
) :
    row0(m00, m01, m02, m03),
    row1(m10, m11, m12, m13),
    row2(m20, m21, m22, m23)
{
}

//=============================================================================
Matrix34::Matrix34 (const Matrix33 & m, const Vector3 & t) :
    row0(m.row0, t.x),
    row1(m.row1, t.y),
    row2(m.row2, t.z)
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

    row[0] = Vector4(1.0f - yy - zz,           xy - zw,            xz + yw,     0.0f);
    row[1] = Vector4(       xy + zw,    1.0f - xx - zz,            yz - xw,     0.0f);
    row[2] = Vector4(       xz - yw,           yz + xw,     1.0f - xx - yy,     0.0f);
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

    row[0] = Vector4(1.0f - yy - zz,           xy - zw,            xz + yw,     t.x);
    row[1] = Vector4(       xy + zw,    1.0f - xx - zz,            yz - xw,     t.y);
    row[2] = Vector4(       xz - yw,           yz + xw,     1.0f - xx - yy,     t.z);  
}



//*****************************************************************************
//
// Matrix44
//
//*****************************************************************************

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
    MemCopy(ma, m.ma);
}

//=============================================================================
Matrix44::Matrix44 ( 
    const Vector4 & r0,
    const Vector4 & r1,
    const Vector4 & r2,
    const Vector4 & r3
) :
    row0(r0),
    row1(r1),
    row2(r2),
    row3(r3)
{
}

//=============================================================================
Matrix44::Matrix44 (
    float32 m00, float32 m01, float32 m02, float32 m03,
    float32 m10, float32 m11, float32 m12, float32 m13,
    float32 m20, float32 m21, float32 m22, float32 m23,
    float32 m30, float32 m31, float32 m32, float32 m33
) :
    row0(m00, m01, m02, m03),
    row1(m10, m11, m12, m13),
    row2(m20, m21, m22, m23),
    row3(m30, m31, m32, m33)
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

    row[0] = Vector4(1.0f - yy - zz,        xy - zw,        xz + yw, 0.0f);
    row[1] = Vector4(       xy + zw, 1.0f - xx - zz,        yz - xw, 0.0f);
    row[2] = Vector4(       xz - yw,        yz + xw, 1.0f - xx - yy, 0.0f); 
    row[3] = Vector4(          0.0f,           0.0f,           0.0f, 1.0f);
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

    row[0] = Vector4(1.0f - yy - zz,        xy - zw,        xz + yw, t.x);
    row[1] = Vector4(       xy + zw, 1.0f - xx - zz,        yz - xw, t.y);
    row[2] = Vector4(       xz - yw,        yz + xw, 1.0f - xx - yy, t.z);  
    row[3] = Vector4(          0.0f,           0.0f,           0.0f, 1.0f);
}

//=============================================================================
const float32 & Matrix22::operator() (uint32 r, uint32 c) const { return row[r][c]; }
const float32 & Matrix33::operator() (uint32 r, uint32 c) const { return row[r][c]; }
const float32 & Matrix34::operator() (uint32 r, uint32 c) const { return row[r][c]; }
const float32 & Matrix44::operator() (uint32 r, uint32 c) const { return row[r][c]; }

//=============================================================================
float32 & Matrix22::operator() (uint32 r, uint32 c) { return row[r][c]; }
float32 & Matrix33::operator() (uint32 r, uint32 c) { return row[r][c]; }
float32 & Matrix34::operator() (uint32 r, uint32 c) { return row[r][c]; }
float32 & Matrix44::operator() (uint32 r, uint32 c) { return row[r][c]; }

//=============================================================================
Matrix44 Matrix44::CreateProjection (float32 left, float32 right, float32 top, float32 bottom, float32 near, float32 far)
{
    return Matrix44(
        2.0f / (right - left), 0.0f,                  0.0f,                -(right + left) / (right - left),
        0.0f,                  2.0f / (top - bottom), 0.0f,                -(top + bottom) / (top - bottom),
        0.0f,                  0.0f,                  1.0f / (far - near), -(far + near) / (far - near),
        0.0f,                  0.0f,                  0.0f,                1.0f
    );
}

//=============================================================================
Matrix44 Matrix44::CreateProjection (float32 width, float32 height, float32 near, float32 far)
{
    const float32 n = near;
    const float32 f = far;
    const float32 w = width;
    const float32 h = height;
    return Matrix44(
        2.0f / w, 0.0f,     0.0f,               0.0f,
        0.0f,     2.0f / h, 0.0f,               0.0f,
        0.0f,     0.0f,     1.0f / (f - n),     0.0f,
        0.0f,     0.0f,     -(f + n) / (f - n), 1.0f
    );
}

//=============================================================================
Matrix44 Matrix44::CreateProjection (float32 aspect, Radian vFov, float32 n, float32 f)
{
    const float cotan = 1.0f / Tan(vFov /2.0f);
    return Matrix44(
		cotan/aspect, 0,           0,     0,
	    0,            (f+n)/(f-n), 0,     (-2.0f*n*f)/(f-n),
		0,            0,           cotan, 0,
		0,            1,           0,     0
    );
}

//=============================================================================
Matrix44 Matrix44::CreateView (const Point3 & eye, const Vector3 & forward, const Vector3 & up)
{   
    const Vector3 & zAxis = Normalize(forward);
    const Vector3 & yAxis = Normalize(up);
    const Vector3 & xAxis = Cross(zAxis, yAxis);

    return Matrix44(
        xAxis.x,  yAxis.x,  zAxis.x, -Dot(xAxis, eye),
        xAxis.y,  yAxis.y,  zAxis.y, -Dot(yAxis, eye),
        xAxis.z,  yAxis.z,  zAxis.z, -Dot(zAxis, eye),
        0.0f,     0.0f,     0.0f,    1.0f
    );

    return Matrix44(
        xAxis.x,  xAxis.y,  xAxis.z, -Dot(xAxis, eye),
        yAxis.x,  yAxis.y,  yAxis.z, -Dot(yAxis, eye),
        zAxis.x,  zAxis.y,  zAxis.z, -Dot(zAxis, eye),
        0.0f,     0.0f,     0.0f,    1.0f
    );
}

//=============================================================================
Matrix44 Matrix44::CreateView (const Point3 & eye, const Point3 & at, const Vector3 & up)
{
    const Vector3 & forward = at - eye;
    return CreateView(eye, forward, up);
}


