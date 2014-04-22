//==================================================================================================
//
// File:    MathQuaternion.inl
// Author:  Jason Jackson
// Date:    September 20, 2008
//
// Defines a four dimentional complex number
//==================================================================================================

//=============================================================================
//
// Quaternion
//
//=============================================================================

//=============================================================================
Quaternion::Quaternion()
{
}

//=============================================================================
Quaternion::Quaternion(float32 a, float32 b, float32 c, float32 d) :
    a(a),
    v(b, c, d) 
{
}

//=============================================================================
Quaternion::Quaternion(const Vector4 & v) :
    a(v.x),
    v(v.y, v.z, v.w) 
{
}
 
//=============================================================================
Quaternion::Quaternion(float32 a, const Vector3 & bcd) :
    a(a),
    v(bcd) 
{
}

//=============================================================================
Quaternion::Quaternion(const Vector3 & axis, Radian angle) :
    a(Cos(angle * 0.5f)),
    v(Normalize(axis) * Sin(angle * 0.5f))
{
}

//=============================================================================
Quaternion & Quaternion::operator/=(float32 rhs)
{
    float32 s = 1.0f / rhs;
    operator*=(s);
    return *this;
}

//=============================================================================
Quaternion & Quaternion::operator*=(float32 rhs)
{
    a *= rhs;
    v /= rhs;
    return *this;
}



//=============================================================================
//
// Binary operators
//
//=============================================================================

//=============================================================================
Quaternion operator+(const Quaternion & lhs, const Quaternion & rhs)
{
    return Quaternion(lhs.a + rhs.a, lhs.v + rhs.v);
}

//=============================================================================
Quaternion operator-(const Quaternion & lhs, const Quaternion & rhs)
{
    return Quaternion(lhs.a - rhs.a, lhs.v - rhs.v);
}

//=============================================================================
Quaternion operator/(const Quaternion & lhs, float32 rhs)
{
    return lhs * (1.0f / rhs);
}

//=============================================================================
Quaternion operator*(const Quaternion & lhs, float32 rhs)
{
    return Quaternion(lhs.a * rhs, lhs.v * rhs);
}

//=============================================================================
Quaternion operator*(float32 lhs, const Quaternion & rhs)
{
    return rhs * lhs;
}

//=============================================================================
Quaternion operator*(const Quaternion & lhs, const Quaternion & rhs)
{
    return Quaternion(
        lhs.a * rhs.a - Dot(lhs.v, rhs.v),
        lhs.a * rhs.v + rhs.a * lhs.v + Cross(lhs.v, rhs.v)
    );
}

//=============================================================================
Quaternion operator-(const Quaternion & q)
{
    return Quaternion(-q.a, -q.v);
}

//=============================================================================
Vector3 operator*(const Quaternion & lhs, const Vector3 & rhs)
{
    return (lhs * Quaternion(0.0f, rhs) * Conjugate(lhs)).v;
}

//=============================================================================
Vector4 operator*(const Quaternion & lhs, const Vector4 & rhs)
{
    return Vector4(lhs * Quaternion(0.0f, rhs.x, rhs.y, rhs.z) * Conjugate(lhs));
}

//=============================================================================
Vector3 operator*(const Vector3 & lhs, const Quaternion & rhs)
{
    return (rhs * Quaternion(0.0f, lhs) * Conjugate(rhs)).v;
}

//=============================================================================
Vector4 operator*(const Vector4 & lhs, const Quaternion & rhs)
{
    return Vector4(rhs * Quaternion(0.0f, lhs.x, lhs.y, lhs.z) * Conjugate(rhs));
}



//=============================================================================
//
// Free Functions
//
//=============================================================================

//=============================================================================
float32 Dot(const Quaternion & lhs, const Quaternion & rhs)
{
    return lhs.a * rhs.a + Dot( lhs.v, rhs.v );
}

//=============================================================================
float32 Length(const Quaternion & q)
{
    return Sqrt(LengthSq(q));
}

//=============================================================================
float32 LengthSq(const Quaternion & q)
{
    return Dot(q, q);
}

//=============================================================================
Quaternion Normalize(const Quaternion & q)
{ 
    const float32 len = Length(q);

    ASSERT(!Equal(len, 0.0f));

    return q / len;
}

//=============================================================================
float32 Normalize2(Quaternion & q)
{ 
    const float32 length = Length(q);
    q /= length; 
    return length;
}

//=============================================================================
Quaternion Conjugate(const Quaternion & q)
{ 
    return Quaternion(q.a, -q.v);
}

//=============================================================================
Quaternion Inverse(const Quaternion & q)
{ 
    return Conjugate(q) / LengthSq(q); 
}

//=============================================================================
Quaternion Pow(const Quaternion & q, float32 t)
{ 
    return Exp(Ln(q) * t); 
}
