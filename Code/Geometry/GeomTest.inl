//==================================================================================================
//
// File:    GeomTest.inl
// Author:  Jason Jackson
// Date:    December 5th, 2008
//
// Tests the positiong of one object compared to a second
//
//=================================================================================================

//=============================================================================
// 
//    Test
//    
// Description: 
//    Gathers information about the relative position of a sphere to a plane
//    
// Parameters: 
//    [const Sphere3 & s] - Sphere to be tested
//    [const Plane3 & p] - 
//    
// Return: 
//    [GeomTestResult] - Relative information about the sphere
//=============================================================================
GeomTestResult Test( const Sphere3 & s, const Plane3 & p )
{
    float32 dist = Distance( s.center, p );

    if( dist > s.radius )       return Outside;
    else if( dist < -s.radius ) return Inside;
    else                        return Straddle;
}


//=============================================================================
// 
//    Test
//    
// Description: 
//    Tests the relative position of an oriented bounding box to a plane
//    
// Parameters: 
//    [const Obb3 & b] - Box to test
//    [const Plane3 & p] - Plane to test against
//    
// Return: 
//    [GeomTestResult] - The relative positioning of the box
//=============================================================================
GeomTestResult Test( const Obb3 & b, const Plane3 & p )
{
    float32 dist = Distance( b.center, p );
    float32 radius = b.ProjectedRadiusAlongVector( p.n );

    if( dist > radius )         return Outside;
    else if( dist < -radius )   return Inside;
    else                        return Straddle;
}


//=============================================================================
// 
//    Test
//    
// Description: 
//    Computes the relative position of an axis-aligned bounding box to a plane
//    
// Parameters: 
//    [const Aabb3 & b] - Box to test
//    [const Plane3 & p] - Plane to test against
//    
// Return: 
//    [GeomTestResult] - Relative positioning of the box
//=============================================================================
GeomTestResult Test( const Aabb3 & b, const Plane3 & p )
{
    p3 center = (v3(b.min) + v3(b.max)) * 0.5f;
    v3 extent = b.max - center;

    float radius = extent.x * Abs(p.n.x) + extent.y * Abs(p.n.y) + extent.z * Abs(p.n.z);

    float dist = Distance( center, p );

    if( dist > radius )         return Outside;
    else if( dist < -radius )   return Inside;
    else                        return Straddle;
}