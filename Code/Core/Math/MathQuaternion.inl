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
//    Quaternion::Quaternion
//    
// Description: 
//   Leaves the quaternion uninitialized
//=============================================================================
Quaternion::Quaternion()
{
}


//=============================================================================
// 
//    Quaternion::Quaternion
//    
// Description: 
//    Sets the components of the quaternion
//    
// Parameters: 
//    [float32 a] - Real component
//    [float32 b] - Imaginary i-axis
//    [float32 c] - Imaginary j-axis
//    [float32 d] - Imaginary k-axis
//=============================================================================
Quaternion::Quaternion( float32 a, float32 b, float32 c, float32 d ) 
: a(a)
, v(b, c, d) 
{
}

//=============================================================================
// 
//    Quaternion::Quaternion
//    
// Description: 
//    Sets the components of this quaternion from a Vector4
//    
// Parameters: 
//    [const Vector4 & v] - the vector in which to copy components from
//    
//=============================================================================
Quaternion::Quaternion( const Vector4 & v ) 
: a(v.x)
, v(v.y, v.z, v.w) 
{
}

//=============================================================================
// 
//    Quaternion::Quaternion
//    
// Description: 
//    Sets the components of the quaternion based on a scalar and a Vector3.
//    This is not an axis angle conversions!
//    
// Parameters: 
//    [float32 a] - Real component
//    [const Vector3 & bcd] - Imaginary components
//    
//=============================================================================
Quaternion::Quaternion( float32 a, const Vector3 & bcd ) 
: a(a)
, v(bcd) 
{
}


//=============================================================================
// 
//    Quaternion::Quaternion
//    
// Description: 
//    Converts an axis-angle pair to a quaternion
//    
// Parameters: 
//    [const Vector3 & axis] - Axis of the rotation (does not have to be normalized)
//    [float32 angle] - Angle of the rotation around the axis
//    
//=============================================================================
Quaternion::Quaternion( const Vector3 & axis, Radian angle ) 
: a( Cos( angle * 0.5f ) )
, v( Normalize(axis) * Sin( angle * 0.5f ) ) 
{
}




Quaternion & Quaternion::operator/=( float32 rhs ) { float32 s = 1.0f / rhs; operator*=( s ); return *this; }
Quaternion & Quaternion::operator*=( float32 rhs ) { a *= rhs; v /= rhs; return *this; }


// Addition
Quaternion  operator+( const Quaternion & lhs, const Quaternion & rhs ) { return Quaternion( lhs.a + rhs.a, lhs.v + rhs.v ); }
Quaternion  operator-( const Quaternion & lhs, const Quaternion & rhs ) { return Quaternion( lhs.a - rhs.a, lhs.v - rhs.v ); }

// Scalar operatopms
Quaternion  operator/( const Quaternion & lhs, float32 rhs )                { return lhs * (1.0f / rhs); }
Quaternion  operator*( const Quaternion & lhs, float32 rhs )                { return Quaternion( lhs.a * rhs, lhs.v * rhs ); }
Quaternion  operator*( float32 lhs, const Quaternion & rhs )                { return rhs * lhs; }

// Multiplication
Quaternion  operator*( const Quaternion & lhs, const Quaternion & rhs ) { return Quaternion( lhs.a * rhs.a - Dot( lhs.v, rhs.v ), lhs.a * rhs.v + rhs.a * lhs.v + Cross( lhs.v, rhs.v ) ); }

// Negate
Quaternion  operator-( const Quaternion & q )                           { return Quaternion( -q.a, -q.v ); }

// Rotate a point
Vector3     operator*( const Quaternion & lhs, const Vector3 & rhs )        { return (lhs * Quaternion(0.0f, rhs) * Conjugate(lhs)).v; }
Vector4     operator*( const Quaternion & lhs, const Vector4 & rhs )        { return Vector4(lhs * Quaternion(0.0f, rhs.x, rhs.y, rhs.z) * Conjugate(lhs)); }
Vector3     operator*( const Vector3 & lhs, const Quaternion & rhs )        { return (rhs * Quaternion(0.0f, lhs) * Conjugate(rhs)).v; }
Vector4     operator*( const Vector4 & lhs, const Quaternion & rhs )        { return Vector4(rhs * Quaternion(0.0f, lhs.x, lhs.y, lhs.z) * Conjugate(rhs)); }



//=============================================================================
// 
//    Dot
//    
// Description: 
//    Dot product between two quaternions
//    
// Parameters: 
//    [const Quaternion & lhs] - quaternion on the left hand side of the product
//    [const Quaternion & rhs] - quaternion on the right hand side of the product
//    
// Return: 
//    [float32] - Scalar 
//=============================================================================
float32 Dot( const Quaternion & lhs, const Quaternion & rhs )
{
    return lhs.a * rhs.a + Dot( lhs.v, rhs.v );
}


//=============================================================================
// 
//    Length
//    
// Description: 
//    Computes the length of this quaternion
//    
// Parameters: 
//    [const Quaternion & q] - quaternion to compute the length
//    
// Return: 
//    [float32] - Scalar length
//=============================================================================
float32 Length( const Quaternion & q )
{
    return Sqrt( LengthSq(q) );
}


//=============================================================================
// 
//    LengthSq
//    
// Description: 
//    Returns the sqruared length of of this quaternion
//    
// Parameters: 
//    [const Quaternion & q] - quaternion to compute the length of
//    
// Return: 
//    [float32] - Scalar length
//=============================================================================
float32 LengthSq( const Quaternion & q )
{
    return Dot( q, q );
}

//=============================================================================
// 
//    Normalize
//    
// Description: 
//    Normalizes a quaternion
//    
// Parameters: 
//    [const Quaternion & q] - The quaternion to normalize
//    
// Return: 
//    [Quaternion] - A copy of the input quaternion scaled to have length = 1.0
//=============================================================================
Quaternion Normalize( const Quaternion & q )
{ 
    float32 len = Length( q );

    assert( !Equal( len, 0.0f ) );

    return q / len;
}


//=============================================================================
// 
//    Normalize2
//    
// Description: 
//    Scales the input quaternion so the it has length = 1.0
//    
// Parameters: 
//    [Quaternion & q] - Quaternion to modify
//    
// Return: 
//    [float32] - The length of the quaternion before normalization
//=============================================================================
float32 Normalize2( Quaternion & q )
{ 
    float32 length = Length( q ); 
    q /= length; 
    return length;
}


//=============================================================================
// 
//    Conjugate
//    
// Description: 
//    Computes the conjugate of the quaternion. 
//    
// Parameters: 
//    [const Quaternion & q] - input quaternion to find the conjugate of
//    
// Return: 
//    [Quaternion] - if q = a + v, returns a - v
//=============================================================================
Quaternion Conjugate( const Quaternion & q )
{ 
    return Quaternion( q.a, -q.v ); 
}


//=============================================================================
// 
//    Inverse
//    
// Description: 
//    Computes an inverted quaternion
//    
// Parameters: 
//    [const Quaternion & q] - input quaternion to invert
//    
// Return: 
//    [Quaternion] - 
//=============================================================================
Quaternion Inverse( const Quaternion & q )
{ 
    return Conjugate(q) / LengthSq(q); 
}


//=============================================================================
// 
//    Pow
//    
// Description: 
//    Take the quaternion exponention q^t
//    
// Parameters: 
//    [const Quaternion & q] - quaternion base of the exponentiation
//    [float32 t] - To what degree to take the quaternion to
//    
// Return: 
//    [Quaternion] - q^t
//=============================================================================
Quaternion Pow( const Quaternion & q, float32 t )
{ 
    return Exp( Ln(q) * t ); 
}
