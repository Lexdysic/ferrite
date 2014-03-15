//==================================================================================================
//
// File:    MathPoint.inl
// Author:  Jason Jackson
// Date:    September 20, 2008
//
// Defines a point as a separate type from vector
//==================================================================================================

//=============================================================================
Point2::Point2()
{
}

//=============================================================================
Point2::Point2( const Vector2 & v )
: Vector2(v)
{
}

//=============================================================================
Point2::Point2( float32 x, float32 y )
: Vector2(x,y)
{
}

//-------------------------------------------------------------------------------------------------------------------------//

//=============================================================================
Point3::Point3()
{
}

//=============================================================================
Point3::Point3( const Vector3 & v )
: Vector3(v)
{
}

//=============================================================================
Point3::Point3( float32 x, float32 y, float32 z )
: Vector3(x,y,z)
{
}

Vector2 operator-( const Point2 & lhs,  const Point2 & rhs )        { return Vector2( lhs.x - rhs.x, lhs.y - rhs.y ); }
Point2  operator-( const Point2 & lhs,  const Vector2 & rhs )   { return Point2(  lhs.x - rhs.x, lhs.y - rhs.y ); }
Point2  operator+( const Point2 & lhs,  const Vector2 & rhs )   { return Point2(  lhs.x + rhs.x, lhs.y + rhs.y ); }
Point2  operator+( const Vector2 & lhs, const Point2 & rhs )        { return Point2(  lhs.x + rhs.x, lhs.y + rhs.y ); }

//----------------------------------------------------------------------------------------------------//

Vector3 operator-( const Point3 & lhs,  const Point3 & rhs )    { return Vector3( lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z ); }
Point3  operator-( const Point3 & lhs,  const Vector3 & rhs )   { return Point3(  lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z ); }
Point3  operator+( const Point3 & lhs,  const Vector3 & rhs )   { return Point3(  lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z ); }
Point3  operator+( const Vector3 & lhs, const Point3 & rhs )    { return Point3(  lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z ); }

//----------------------------------------------------------------------------------------------------//
 
float32 Min( const Point2 & v ) { return Min( v.x, v.y ); }
float32 Min( const Point3 & v ) { return Min( Min( v.x, v.y), v.z ); }

//----------------------------------------------------------------------------------------------------//

Point2  Min( const Point2 & a, const Point2 & b ) { return Point2( Min(a.x, b.x), Min(a.y, b.y) ); }
Point3  Min( const Point3 & a, const Point3 & b ) { return Point3( Min(a.x, b.x), Min(a.y, b.y), Min(a.z, b.z) ); }

//----------------------------------------------------------------------------------------------------//

float32 Max( const Point2 & v ) { return Max( v.x, v.y ); }
float32 Max( const Point3 & v ) { return Max( Max( v.x, v.y), v.z ); }

//----------------------------------------------------------------------------------------------------//

Point2  Max( const Point2 & a, const Point2 & b ) { return Point2( Max(a.x, b.x), Max(a.y, b.y) ); }
Point3  Max( const Point3 & a, const Point3 & b ) { return Point3( Max(a.x, b.x), Max(a.y, b.y), Max(a.z, b.z) ); }