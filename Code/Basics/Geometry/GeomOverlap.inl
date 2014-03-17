//==================================================================================================
//
// File:    GeomOverlap.inl
// Author:  Jason Jackson
// Date:    September 21, 2008
//
// Provides a way to test if two shapes are overlapping
//
//==================================================================================================

//=============================================================================
// 
//    Overlap
//    
// Description: 
//    Tests if any part of a two spheres overlap. They are considered solid.
//    
// Parameters: 
//    [const Sphere2 & a] - 
//    [const Sphere2 & b] - 
//    
// Return: 
//    [bool] - True if they overlap in any way, false otherwise
//=============================================================================
bool Overlap( const Sphere2 & a, const Sphere2 & b )
{
    return DistanceSq(a.center, b.center) <= Sq(a.radius + b.radius);
}

//=============================================================================
// 
//    Overlap
//    
// Description: 
//    Tests if any part of a two spheres overlap. They are considered solid.
//    
// Parameters: 
//    [const Sphere3 & a] - 
//    [const Sphere3 & b] - 
//    
// Return: 
//    [bool] - True if they overlap in any way, false otherwise
//=============================================================================
bool Overlap( const Sphere3 & a, const Sphere3 & b )
{
    return DistanceSq(a.center, b.center) <= Sq(a.radius + b.radius);
}

//=============================================================================
// 
//    Overlap
//    
// Description: 
//    Tests if any part of two axis-aligned bounding box overlap. They are considered solid.
//    
// Parameters: 
//    [const Aabb3 & a] - 
//    [const Aabb3 & b] - 
//    
// Return: 
//    [bool] - True if the two boxes overlap
//=============================================================================
bool Overlap( const Aabb3 & a, const Aabb3 & b )
{
    if( a.max.x < b.min.x || a.min.x > b.max.x ) return false;
    if( a.max.y < b.min.y || a.min.y > b.max.y ) return false;
    if( a.max.z < b.min.z || a.min.z > b.max.z ) return false;
    return true;
}

//=============================================================================
// 
//    Overlap
//    
// Description: 
//    Tests if any part of two capsules overlap. They are considered solid.
//    
// Parameters: 
//    [const Capsule3 & cap1] - 
//    [const Capsule3 & cap2] - 
//    
// Return: 
//    [bool] - True if the two capsules are touching.
//=============================================================================
bool Overlap( const Capsule3 & cap1,    const Capsule3 & cap2 )
{
    ClosestInfoSegmentSegment3 info;
    ClosestInfo( info, Segment3(cap1.a, cap1.b), Segment3(cap2.a, cap2.b) );
    
    return info.distSq <= Sq(cap1.radius + cap2.radius);
}

//=============================================================================
// 
//    Overlap
//    
// Description: 
//    Test if any part of a sphere and capsule overlap. They are considered solid.
//    
// Parameters: 
//    [const Sphere3 & s] - 
//    [const Capsule3 & c] - 
//    
// Return: 
//    [bool] - True if they are found overlapping, false otherwise.
//=============================================================================
bool Overlap( const Sphere3 & s,    const Capsule3 & c )
{
    return DistanceSq( s.center, c.seqment ) <= Sq(s.radius + c.radius);
}

//=============================================================================
// 
//    Overlap
//    
// Description: 
//    Tests if any part of a sphere and axis-aligned bounding box overlap. They are considered solid.
//    
// Parameters: 
//    [const Sphere3 & s] - 
//    [const Aabb3 & b] - 
//    
// Return: 
//    [bool] - True if they touch, false otherwise
//=============================================================================
bool Overlap( const Sphere3 & s, const Aabb3 & b )
{
    return DistanceSq(s.center, b) <= Sq(s.radius);
}

//=============================================================================
// 
//    Overlap
//    
// Description: 
//    Tests if any part of a sphere and orientent bounding box overlap. They are considered solid.
//    
// Parameters: 
//    [const Sphere3 & s] - 
//    [const Obb3 & b] - 
//    
// Return: 
//    [bool] - True if they touch, false otherwise
//=============================================================================
bool Overlap( const Sphere3 & s, const Obb3 & b )
{
    return DistanceSq(s.center, b) <= Sq(s.radius);
}

//=============================================================================
bool Overlap (const Aabb2 & box, const Segment2 & line)
{
    return Overlap(line, box);
}

//=============================================================================
bool Contains (const Aabb2 & a, const Point2 & p)
{
    return
        Math::IsInRange(p.x, a.min.x, a.max.x) &&
        Math::IsInRange(p.y, a.min.y, a.max.y);
}