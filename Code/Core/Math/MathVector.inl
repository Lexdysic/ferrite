//==================================================================================================
//
// File:    MathVector.inl
// Author:  Jason Jackson
// Date:    September 24, 2008
//
// Implementation of inline vector operators
//
//==================================================================================================

Vector2::Vector2() {}
Vector2::Vector2( const Vector2 & v )   : x(v.x), y(v.y) {}
Vector2::Vector2( float32 c1, float32 c2 )      : x(c1), y(c2) {}

//----------------------------------------------------------------------------------------------------//

Vector3::Vector3() {}
Vector3::Vector3( const Vector3 & v )           : x(v.x),   y(v.y),   z(v.z)   {}
Vector3::Vector3( const Vector2 & c12, float32 c3 ) : x(c12.x), y(c12.y), z(c3)    {}
Vector3::Vector3( float32 c1, const Vector2 & c23 ) : x(c1),    y(c23.x), z(c23.y) {}
Vector3::Vector3( float32 c1, float32 c2, float32 c3 )      : x(c1),    y(c2),    z(c3)    {}

//----------------------------------------------------------------------------------------------------//

Vector4::Vector4() {}
Vector4::Vector4( const Point3 & p )                : x(p.x),   y(p.y),     z(p.z),     w(1.0f) {}
Vector4::Vector4( const Vector3 & v )               : x(v.x),   y(v.y),     z(v.z),     w(0.0f) {}
Vector4::Vector4( const Vector4 & v )               : x(v.x),   y(v.y),     z(v.z),     w(v.w) {}
Vector4::Vector4( const Vector3 & xyz, float32 c4 )     : x(xyz.x), y(xyz.y),   z(xyz.z),   w(c4) {}
Vector4::Vector4( float32 c1, const Vector3 & c234 )         : x(c1),    yzw(c234) {}
Vector4::Vector4( const Vector2 & c12, const Vector2 & c34 )  : xy(c12),              zw(c34) {}
Vector4::Vector4( float32 c1, const Vector2 & c23, float32 c4 )  : x(c1),    yz(c23),                w(c4) {}
Vector4::Vector4( float32 c1, float32 c2, float32 c3, float32 c4 )  : x(c1),    y(c2),      z(c3),      w(c4) {}
Vector4::Vector4( const q32 & q )                   : x(q.v.x), y(q.v.y),   z(q.v.z),   w(q.a) {}

//----------------------------------------------------------------------------------------------------//

Vector2 & Vector2::operator=( const Vector2 & v ) { if( this != &v ) { x = v.x; y = v.y; } return *this; }
Vector3 & Vector3::operator=( const Vector3 & v ) { if( this != &v ) { x = v.x; y = v.y; z = v.z; } return *this; }
Vector4 & Vector4::operator=( const Vector4 & v ) { if( this != &v ) { x = v.x; y = v.y; z = v.z; w = v.w; } return *this; }

//----------------------------------------------------------------------------------------------------//

Vector2 & Vector2::operator/=( const Vector2 & v ) { x /= v.x; y /= v.y; return *this; }
Vector3 & Vector3::operator/=( const Vector3 & v ) { x /= v.x; y /= v.y; z /= v.z; return *this; }
Vector4 & Vector4::operator/=( const Vector4 & v ) { x /= v.x; y /= v.y; z /= v.z; w /= v.x; return *this; }

//----------------------------------------------------------------------------------------------------//

Vector2 & Vector2::operator*=( const Vector2 & v ) { x *= v.x; y *= v.y; return *this; }
Vector3 & Vector3::operator*=( const Vector3 & v ) { x *= v.x; y *= v.y; z *= v.z; return *this; }
Vector4 & Vector4::operator*=( const Vector4 & v ) { x *= v.x; y *= v.y; z *= v.z; w *= v.x; return *this; }

//----------------------------------------------------------------------------------------------------//

Vector2 & Vector2::operator/=( float32 s ) { float32 m = 1.0f / s; x *= m; y *= m; return *this; }
Vector3 & Vector3::operator/=( float32 s ) { float32 m = 1.0f / s; x *= m; y *= m; z *= m; return *this; }
Vector4 & Vector4::operator/=( float32 s ) { float32 m = 1.0f / s; x *= m; y *= m; z *= m; w *= m; return *this; }

//----------------------------------------------------------------------------------------------------//

Vector2 & Vector2::operator*=( float32 s ) { x *= s; y *= s; return *this; }
Vector3 & Vector3::operator*=( float32 s ) { x *= s; y *= s; z *= s; return *this; }
Vector4 & Vector4::operator*=( float32 s ) { x *= s; y *= s; z *= s; w *= s; return *this; }

//----------------------------------------------------------------------------------------------------//

Vector2 & Vector2::operator+=( const Vector2 & v ) { x += v.x; y += v.y; return *this; }
Vector3 & Vector3::operator+=( const Vector3 & v ) { x += v.x; y += v.y; z += v.z; return *this; }
Vector4 & Vector4::operator+=( const Vector4 & v ) { x += v.x; y += v.y; z += v.z; w += v.w; return *this; }

//----------------------------------------------------------------------------------------------------//

Vector2 & Vector2::operator-=( const Vector2 & v ) { x -= v.x; y -= v.y; return *this; }
Vector3 & Vector3::operator-=( const Vector3 & v ) { x -= v.x; y -= v.y; z -= v.z; return *this; }
Vector4 & Vector4::operator-=( const Vector4 & v ) { x -= v.x; y -= v.y; z -= v.z; w -= v.w; return *this; }

//----------------------------------------------------------------------------------------------------//

const float32 & Vector2::operator[]( uint i ) const { return (&x)[i]; }
const float32 & Vector3::operator[]( uint i ) const { return (&x)[i]; }
const float32 & Vector4::operator[]( uint i ) const { return (&x)[i]; }

//----------------------------------------------------------------------------------------------------//

float32 & Vector2::operator[]( uint i ) { return (&x)[i]; }
float32 & Vector3::operator[]( uint i ) { return (&x)[i]; }
float32 & Vector4::operator[]( uint i ) { return (&x)[i]; }

//----------------------------------------------------------------------------------------------------//

Vector2  operator+( const Vector2 & lhs,  const Vector2 & rhs ) { return Vector2( lhs.x + rhs.x, lhs.y + rhs.y); }
Vector3  operator+( const Vector3 & lhs,  const Vector3 & rhs ) { return Vector3( lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z ); }
Vector4  operator+( const Vector4 & lhs,  const Vector4 & rhs ) { return Vector4( lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z, lhs.w + rhs.w ); }

//----------------------------------------------------------------------------------------------------//

Vector2  operator-( const Vector2 & lhs,  const Vector2 & rhs ) { return Vector2( lhs.x - rhs.x, lhs.y - rhs.y ); }
Vector3  operator-( const Vector3 & lhs,  const Vector3 & rhs ) { return Vector3( lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z ); }
Vector4  operator-( const Vector4 & lhs,  const Vector4 & rhs ) { return Vector4( lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z, lhs.w - rhs.w ); }

//----------------------------------------------------------------------------------------------------//

Vector2  operator*( const float32 & lhs, const Vector2 & rhs ) { return Vector2( lhs * rhs.x, lhs * rhs.y ); }
Vector3  operator*( const float32 & lhs, const Vector3 & rhs ) { return Vector3( lhs * rhs.x, lhs * rhs.y, lhs * rhs.z ); }
Vector4  operator*( const float32 & lhs, const Vector4 & rhs ) { return Vector4( lhs * rhs.x, lhs * rhs.y, lhs * rhs.z, lhs * rhs.w ); }

//----------------------------------------------------------------------------------------------------//

Vector2  operator*( const Vector2 & lhs,  const float32 & rhs ) { return Vector2( lhs.x * rhs, lhs.y * rhs ); }
Vector3  operator*( const Vector3 & lhs,  const float32 & rhs ) { return Vector3( lhs.x * rhs, lhs.y * rhs, lhs.z * rhs ); }
Vector4  operator*( const Vector4 & lhs,  const float32 & rhs ) { return Vector4( lhs.x * rhs, lhs.y * rhs, lhs.z * rhs, lhs.w * rhs); }

//----------------------------------------------------------------------------------------------------//

Vector2  operator*( const Vector2 & lhs,  const Vector2 & rhs ) { return Vector2( lhs.x * rhs.x, lhs.y * rhs.y ); }
Vector3  operator*( const Vector3 & lhs,  const Vector3 & rhs ) { return Vector3( lhs.x * rhs.x, lhs.y * rhs.y, lhs.z * rhs.z ); }
Vector4  operator*( const Vector4 & lhs,  const Vector4 & rhs ) { return Vector4( lhs.x * rhs.x, lhs.y * rhs.y, lhs.z * rhs.z, lhs.w * rhs.w ); }

//----------------------------------------------------------------------------------------------------//

Vector2  operator/( const Vector2 & lhs,  const Vector2 & rhs ) { return Vector2( lhs.x / rhs.x, lhs.y / rhs.y ); }
Vector3  operator/( const Vector3 & lhs,  const Vector3 & rhs ) { return Vector3( lhs.x / rhs.x, lhs.y / rhs.y, lhs.z / rhs.z ); }
Vector4  operator/( const Vector4 & lhs,  const Vector4 & rhs ) { return Vector4( lhs.x / rhs.x, lhs.y / rhs.y, lhs.z / rhs.z, lhs.w / rhs.w ); }

//----------------------------------------------------------------------------------------------------//

Vector2  operator/( const Vector2 & lhs,  const float32 & rhs ) { return lhs * (1.0f / rhs); }
Vector3  operator/( const Vector3 & lhs,  const float32 & rhs ) { return lhs * (1.0f / rhs); }
Vector4  operator/( const Vector4 & lhs,  const float32 & rhs ) { return lhs * (1.0f / rhs); }

//----------------------------------------------------------------------------------------------------//

Vector2  operator-( const Vector2 & v ) { return Vector2( -v.x, -v.y ); }
Vector3  operator-( const Vector3 & v ) { return Vector3( -v.x, -v.y, -v.z ); }
Vector4  operator-( const Vector4 & v ) { return Vector4( -v.x, -v.y, -v.z, -v.w ); }

//=============================================================================
bool operator==( const Vector2 & lhs, const Vector2 & rhs ) 
{ 
    return lhs.x == rhs.x && 
           lhs.y == rhs.y; 
}

//=============================================================================
bool operator==( const Vector3 & lhs, const Vector3 & rhs ) 
{ 
    return lhs.x == rhs.x && 
           lhs.y == rhs.y && 
           lhs.z == rhs.z; 
}

//=============================================================================
bool operator==( const Vector4 & lhs, const Vector4 & rhs ) 
{ 
    return lhs.x == rhs.x && 
           lhs.y == rhs.y && 
           lhs.z == rhs.z && 
           lhs.w == rhs.z; 
}

//=============================================================================
bool operator!=( const Vector2 & lhs, const Vector2 & rhs ) 
{ 
    return !(lhs == rhs); 
}

//=============================================================================
bool operator!=( const Vector3 & lhs, const Vector3 & rhs ) 
{ 
    return !(lhs == rhs); 
}

//=============================================================================
bool operator!=( const Vector4 & lhs, const Vector4 & rhs ) 
{ 
    return !(lhs == rhs); 
}

//=============================================================================
float32 Dot( const Vector2 & lhs, const Vector2 & rhs ) 
{ 
    return lhs.x * rhs.x + 
           lhs.y * rhs.y; 
}

//=============================================================================
float32 Dot( const Vector3 & lhs, const Vector3 & rhs ) 
{ 
    return lhs.x * rhs.x + 
           lhs.y * rhs.y + 
           lhs.z * rhs.z; 
}

//=============================================================================
float32 Dot( const Vector4 & lhs, const Vector4 & rhs ) 
{ 
    return lhs.x * rhs.x + 
           lhs.y * rhs.y + 
           lhs.z * rhs.z + 
           lhs.w * rhs.w; 
}

//=============================================================================
float32 Cross (const Vector2 & lhs, const Vector2 & rhs)
{ 
    return lhs.x * rhs.y - lhs.y * rhs.x; 
}

//=============================================================================
Vector3 Cross( const Vector3 & lhs, const Vector3 & rhs )
{ 
    return Vector3( 
        lhs.y * rhs.z - lhs.z * rhs.y, 
        lhs.z * rhs.x - lhs.x * rhs.z, 
        lhs.x * rhs.y - lhs.y * rhs.x ); 
}

//=============================================================================
Matrix22 Tensor (const Vector2 & u, const Vector2 & v)
{
    return Matrix22(
        u.x * v.x, u.x * v.y,
        u.y * v.x, u.y * v.y
    );
}

//=============================================================================
Matrix33 Tensor( const Vector3 & u, const Vector3 & v )
{
    return Matrix33(
        u.x * v.x, u.x * v.y, u.x * v.z,
        u.y * v.x, u.y * v.y, u.y * v.z,
        u.z * v.x, u.z * v.y, u.z * v.z
    );
}

//=============================================================================
Vector2  Normalize (const Vector2 & v)
{ 
    const float32 len = Length(v);
    ASSERT(len != 0.0f);

    const float32 recipLen = Inverse(len);

    return Vector2(
        v.x * recipLen,
        v.y * recipLen
    );
}

//=============================================================================
Vector3  Normalize (const Vector3 & v)
{
    const float32 len = Length(v);
    ASSERT(len != 0.0f);

    const float32 recipLen = Inverse(len);

    return Vector3(
        v.x * recipLen,
        v.y * recipLen,
        v.z * recipLen
    );
}

//=============================================================================
Vector4 Normalize (const Vector4 & v)
{ 
    const float32 len = Length(v);
    ASSERT(len != 0.0f);

    const float32 recipLen = Inverse(len);

    return Vector4(
        v.x * recipLen,
        v.y * recipLen,
        v.z * recipLen,
        v.w * recipLen
    );
}

//=============================================================================
Vector2 Normalize (const Vector2 & v, float32 * outLength)
{
    ASSERT(outLength);

    *outLength = Length(v); 
    if (*outLength == 0.0f)
        return v;

    const float32 recipLen = Inverse(*outLength);

    return Vector2(
        v.x * recipLen,
        v.y * recipLen
    );
}

//=============================================================================
Vector3 Normalize (const Vector3 & v, float32 * outLength)
{
    ASSERT(outLength);

    const float32 len = Length(v); 
    ASSERT(len != 0.0f); 

    const float32 recipLen = Inverse(len);

    *outLength = len;

    return Vector3(
        v.x * recipLen,
        v.y * recipLen,
        v.z * recipLen
    );
}

//=============================================================================
Vector4 Normalize (const Vector4 & v, float32 * outLength)
{
    ASSERT(outLength);

    const float32 len = Length(v); 
    ASSERT(len != 0.0f); 
    
    const float32 recipLen = Inverse(len);

    *outLength = len;

    return Vector4(
        v.x * recipLen,
        v.y * recipLen,
        v.z * recipLen,
        v.w * recipLen
    );
}

//----------------------------------------------------------------------------------------------------//

float32 Normalize2( Vector2 & v ) { float32 length = Length( v ); v /= length; return length; }
float32 Normalize2( Vector3 & v ) { float32 length = Length( v ); v /= length; return length; }
float32 Normalize2( Vector4 & v ) { float32 length = Length( v ); v /= length; return length; }

//----------------------------------------------------------------------------------------------------//

float32 Length( const Vector2 & v ) { return Sqrt( LengthSq( v ) ); }
float32 Length( const Vector3 & v ) { return Sqrt( LengthSq( v ) ); }
float32 Length( const Vector4 & v ) { return Sqrt( LengthSq( v ) ); }

//----------------------------------------------------------------------------------------------------//

float32 LengthSq( const Vector2 & v ) { return Dot( v, v ); }
float32 LengthSq( const Vector3 & v ) { return Dot( v, v ); }
float32 LengthSq( const Vector4 & v ) { return Dot( v, v ); }

//----------------------------------------------------------------------------------------------------//

bool Parallel( const Vector2 & a, const Vector2 & b ) { return Sq(Dot(a, b)) > LengthSq(a) * LengthSq(b) * Sq(1.0f-Math::Epsilon); }
bool Parallel( const Vector3 & a, const Vector3 & b ) { return Sq(Dot(a, b)) > LengthSq(a) * LengthSq(b) * Sq(1.0f-Math::Epsilon); }
bool Parallel( const Vector4 & a, const Vector4 & b ) { return Sq(Dot(a, b)) > LengthSq(a) * LengthSq(b) * Sq(1.0f-Math::Epsilon); }

//----------------------------------------------------------------------------------------------------//

bool Perpendicular( const Vector2 & a, const Vector2 & b ) { return Equal( Dot(a, b), 0.0f ); }
bool Perpendicular( const Vector3 & a, const Vector3 & b ) { return Equal( Dot(a, b), 0.0f ); }
bool Perpendicular( const Vector4 & a, const Vector4 & b ) { return Equal( Dot(a, b), 0.0f ); }

//=============================================================================
Vector2 Mirror( const Vector2 & v, const Vector2 & n ) 
{ 
    //assert(Equal(LengthSq(n), 1.0f));
    return v - 2.0f * n * Dot(v, n) / LengthSq(n); // if n is not normalized
    //return v - 2.0f * n * Dot(v, n);
}

//=============================================================================
Vector3 Mirror( const Vector3 & v, const Vector3 & n ) 
{ 
    assert(Equal(LengthSq(n), 1.0f));
    //return v - 2.0f * n * Dot(v, n) / LengthSq(n); // if n is not normalized
    return v - 2.0f * n * Dot(v, n);
}

//=============================================================================
float32 Min( const Vector2 & v ) 
{ 
    return Min( v.x, v.y ); 
}

//=============================================================================
float32 Min( const Vector3 & v ) 
{ 
    return Min( Min( v.x, v.y), v.z ); 
}

//=============================================================================
float32 Min( const Vector4 & v ) 
{ 
    return Min( Min( Min( v.x, v.y ), v.z), v.w ); 
}

//=============================================================================
float32 Max( const Vector2 & v ) 
{ 
    return Max( v.x, v.y ); 
}

//=============================================================================
float32 Max( const Vector3 & v ) 
{ 
    return Max( v.x, v.y, v.z ); 
}

//=============================================================================
float32 Max( const Vector4 & v ) 
{ 
    return Max( Max( Max( v.x, v.y ), v.z), v.w ); 
}

//=============================================================================
Vector2 Min( const Vector2 & a, const Vector2 & b ) 
{ 
    return Vector2( 
        Min(a.x, b.x), 
        Min(a.y, b.y) ); 
}

//=============================================================================
Vector3 Min( const Vector3 & a, const Vector3 & b ) 
{ 
    return Vector3( 
        Min(a.x, b.x), 
        Min(a.y, b.y), 
        Min(a.z, b.z) ); 
}

//=============================================================================
Vector4 Min( const Vector4 & a, const Vector4 & b ) 
{ 
    return Vector4( 
        Min(a.x, b.x), 
        Min(a.y, b.y), 
        Min(a.z, b.z), 
        Min(a.w, b.w) ); 
}

//=============================================================================
Vector2 Max( const Vector2 & a, const Vector2 & b ) 
{ 
    return Vector2( 
        Max(a.x, b.x), 
        Max(a.y, b.y) ); 
}

//=============================================================================
Vector3 Max( const Vector3 & a, const Vector3 & b ) 
{ 
    return Vector3( 
        Max(a.x, b.x), 
        Max(a.y, b.y), 
        Max(a.z, b.z) ); 
}

//=============================================================================
Vector4 Max( const Vector4 & a, const Vector4 & b ) { 
    return Vector4( 
        Max(a.x, b.x), 
        Max(a.y, b.y), 
        Max(a.z, b.z), 
        Max(a.w, b.w) ); 
}

//=============================================================================
Vector2 Abs( const Vector2 & v ) 
{ 
    return Vector2( 
        Abs(v.x), 
        Abs(v.y) ); 
}

//=============================================================================
Vector3 Abs( const Vector3 & v ) 
{ 
    return Vector3( 
        Abs(v.x), 
        Abs(v.y), 
        Abs(v.z) ); 
}

//=============================================================================
Vector4 Abs( const Vector4 & v ) 
{ 
    return Vector4( 
        Abs(v.x), 
        Abs(v.y), 
        Abs(v.z), 
        Abs(v.w) ); 
}

//=============================================================================
inline Vector2 Sign(const Vector2 & v)
{
    return Vector2(
        Sign(v.x), 
        Sign(v.y)
    );
}

//=============================================================================
inline Vector3 Sign(const Vector3 & v) 
{
    return Vector3(
        Sign(v.x), 
        Sign(v.y), 
        Sign(v.z)
    );
}

//=============================================================================
inline Vector4 Sign(const Vector4 & v)
{
    return Vector4(
        Sign(v.x), 
        Sign(v.y), 
        Sign(v.z), 
        Sign(v.w)
    );
}

//=============================================================================
bool Equal( const Vector2 & a, const Vector2 & b, sint32 maxUlps ) 
{ 
    return Equal( a.x, b.x, maxUlps ) && 
           Equal( a.y, b.y, maxUlps ); 
}

//=============================================================================
bool Equal( const Vector3 & a, const Vector3 & b, sint32 maxUlps ) 
{ 
    return Equal( a.x, b.x, maxUlps ) && 
           Equal( a.y, b.y, maxUlps ) && 
           Equal( a.z, b.z, maxUlps ); 
}

//=============================================================================
bool Equal( const Vector4 & a, const Vector4 & b, sint32 maxUlps ) 
{ 
    return Equal( a.x, b.x, maxUlps ) && 
           Equal( a.y, b.y, maxUlps ) && 
           Equal( a.z, b.z, maxUlps ) && 
           Equal( a.w, b.w, maxUlps ); 
}

//=============================================================================
bool Normalized( const Vector2 & v, sint32 maxUlps ) 
{ 
    return Equal( LengthSq( v ), 1.0f, maxUlps ); 
}

//=============================================================================
bool Normalized( const Vector3 & v, sint32 maxUlps ) 
{ 
    return Equal( LengthSq( v ), 1.0f, maxUlps ); 
}

//=============================================================================
bool Normalized( const Vector4 & v, sint32 maxUlps ) 
{ 
    return Equal( LengthSq( v ), 1.0f, maxUlps ); 
}