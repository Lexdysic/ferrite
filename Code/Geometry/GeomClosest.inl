//==================================================================================================
//
// File:    GeomClosest.inl
// Author:  Jason Jackson
// Date:    October 5th, 2008
//
// Implement function which find the closest point(s) between two objects
//
//=================================================================================================

//=============================================================================
// 
//    Closest
//    
// Description: 
//    Returns the closest point on a plane to a point
//    
// Parameters: 
//    [const Point3 & p] - Point to test against
//    [const Plane3 & plane] - Plane to find the closest point on
//    
// Return: 
//    [p3] - The closest point on the plane
//=============================================================================
p3 Closest( const Point3 & p, const Plane3 & plane )
{
    return p - Distance(p, plane) * plane.n;
}


//=============================================================================
// 
//    Closest
//    
// Description: 
//    Returns the closest point on a line to a point
//    
// Parameters: 
//    [const p3 & p] - Point to test
//    [const Line3 & line] - Line of which to find the closest point
//    
// Return: 
//    [p3] - A point on the given line closest to the point
//=============================================================================
p3 Closest( const p3 & p, const Line3 & line )
{
    float32 t = Dot(p - line.origin, line.direction) / LengthSq(line.direction);
    return line.origin + t * line.direction;
}


//=============================================================================
// 
//    Closest
//    
// Description: 
//    Computes the cloests point on a ray to a point
//    
// Parameters: 
//    [const p3 & p] - Point to test against
//    [const Ray3 & line] - Ray to find a point on
//    
// Return: 
//    [p3] - A point on the given ray closest to the point
//=============================================================================
p3 Closest( const p3 & p, const Ray3 &  line )
{
    float32 t = Dot(p - line.origin, line.direction) / LengthSq(line.direction);
    if( t < 0.0f ) t = 0.0f;
    return line.origin + t * line.direction;
}

//=============================================================================
Point3 Closest (const Point3 & p, const Segment3 & line)
{
    const Vector3 v = line.b - line.a;
    float32 t = Dot(p - line.a, v) / LengthSq(v);

    t = Clamp(t, 0.0f, 1.0f);

    return line.a + t * v;
}

//=============================================================================
Point2 Closest (const Point2 & p, const Segment2 & line)
{
    const Vector2 v = line.b - line.a;
    float32 t = Dot(p - line.a, v) / LengthSq(v);

    t = Clamp(t, 0.0f, 1.0f);

    return line.a + t * v;
}

//=============================================================================
// 
//    Closest
//    
// Description: 
//    Computes the closest point on an Axis-aligned bounding box to a point
//    
// Parameters: 
//    [const p3 & p] - Point to test against
//    [const Aabb3 & box] - Box to find a point on
//    
// Return: 
//    [p3] - A point on the given Aabb to the point
//=============================================================================
p3 Closest( const p3 & p, const Aabb3 & box )
{
    p3 out;
    for( uint i = 0; i < 3; ++i )
    {
        out[i] = Clamp( p[i], box.min[i], box.max[i] );
    }

    return out;
}

//=============================================================================
// 
//    Closest
//    
// Description: 
//    Computes the closest point on an Oriented bounding box to a point
//    
// Parameters: 
//    [const p3 & p] - Point to test against
//    [const Obb3 & box] - Box to find a point on
//    
// Return: 
//    [p3] - A point on the given Obb to the point
//=============================================================================
p3 Closest( const p3 & p, const Obb3 & box )
{
    v3 d    = p - box.center;
    p3 out  = box.center;
    for( uint i = 0; i < 3; ++i )
    {
        float32 dist = Dot(d, box.u[i]);
        dist = Clamp( dist, -box.extent[i], box.extent[i] );
        out += dist * box.u[i];
    }
    return out;
}

//=============================================================================
// 
//    Closest
//    
// Description: 
//    Computes the closest point on a rectangle to a point
//    
// Parameters: 
//    [const p3 & p] - Point to test against
//    [const Rect3 & rect] - Rectangle to find a point on
//    
// Return: 
//    [p3] - A point on the given rectangle
//=============================================================================
p3 Closest( const p3 & p, const Rect3 & rect )
{
    v3 d    = p - rect.center;
    p3 out  = rect.center;
    for( uint i = 0; i < 2; ++i )
    {
        float32 dist = Clamp( Dot(d, rect.u[i]), -rect.extent[i], rect.extent[i] );
        out += dist * rect.u[i];
    }
    return out;
}