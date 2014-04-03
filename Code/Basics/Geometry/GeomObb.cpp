//==================================================================================================
//
// File:    GeomObb.cpp
// Author:  Jason Jackson
// Date:    December 5th, 2008
//
// An oriented bounding box which does not align to any native axis
//
//=================================================================================================

#include "GeomPch.h"

//=============================================================================    
Obb2::Obb2()
{
}

//=============================================================================
Obb2::Obb2 (
    const Point2 & center,
    const Vector2 & x,
    const Vector2 & y
) :
    center(center)
{
    u[0] = x;
    u[1] = y;

    for( uint i = 0; i < 2; ++i )
        extent[i] = Normalize2(u[i]);

}

//=============================================================================
Obb2::Obb2 (
    const Point2 & center,
    const Vector2 & unitX,
    const Vector2 & unitY,
    const Vector2 & extent
) :
    center(center),
    extent(extent)
{
    ASSERT(Normalized(unitX));
    ASSERT(Normalized(unitY));
    
    u[0] = unitX;
    u[1] = unitY;
}

//=============================================================================
TArray<Point2> Obb2::GetPoints () const
{
    const Vector2 baseX = u[0] * extent.x;
    const Vector2 baseY = u[1] * extent.y;

    TArray<Point2> out;
    out.Reserve(4);
    out.Add( baseX + baseY + center);
    out.Add( baseX - baseY + center);
    out.Add(-baseX - baseY + center);
    out.Add(-baseX + baseY + center);

    return out;
}


//=============================================================================
// 
//    Obb3::Obb3
//    
// Description: 
//    Constructor that leaves the box uninitialized
//=============================================================================    
Obb3::Obb3()
{
}

//=============================================================================
// 
//    Obb3::Obb3
//    
// Description: 
//    Constructs the box from its center and three orthogonal vectors.
//    
// Parameters: 
//    [const p32 & center] - Center of the box
//    [const v32 & x] - Local x-axis (does not need to be normalized)
//    [const v32 & y] - Local y-axis (does not need to be normalized)
//    [const v32 & z] - Local z-axis (does not need to be normalized)
//    
//=============================================================================
Obb3::Obb3( const Point3 & center, const Vector3 & x, const Vector3 & y, const Vector3 & z )
: center(center)
{
    u[0] = x;
    u[1] = y;
    u[2] = z;

    for( uint i = 0; i < 3; ++i )
        extent[i] = Normalize2( u[i] );

}

//=============================================================================
// 
//    Obb3::Obb3
//    
// Description: 
//    Constructs the box from its center and three ortho-normal vectors and the extents.
//    
// Parameters: 
//    [const Point3 & center] - Center of the box
//    [const v3 & unitX] - Local x-axis (must be normalized)
//    [const v3 & unitY] - Local y-axis (must be normalized)
//    [const v3 & unitZ] - Local z-axis (must be normalized)
//    [const v3 & extent] - Extents in each of the local axes
//    
//=============================================================================
Obb3::Obb3( const Point3 & center, const Vector3 & unitX, const Vector3 & unitY, const Vector3 & unitZ, const Vector3 & extent )
: center(center)
, extent(extent)
{
    assert( Normalized(unitX) );
    assert( Normalized(unitY) );
    assert( Normalized(unitZ) );
    
    u[0] = unitX;
    u[1] = unitY;
    u[2] = unitZ;
}


