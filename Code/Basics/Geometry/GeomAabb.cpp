//==================================================================================================
//
// File:    GeomAABB.cpp
// Author:  Jason Jackson
// Date:    October 5th, 2008
//
// Implements functions related to axis-aligned bounding boxes
//
//=================================================================================================

#include "GeomPch.h"

//=============================================================================
//
// Aabb2
//
//=============================================================================
const Aabb2 Aabb2::Null(Point2::One, Point2::Zero);
const Aabb2 Aabb2::Infinity(-Point2::Infinity, Point2::Infinity);

//=============================================================================
Aabb2::Aabb2()
{
}

//=============================================================================
Aabb2::Aabb2 (const Point2 & min, const Point2 & max) :
    min(min),
    max(max)
{
}

//=============================================================================
Aabb2::Aabb2 (const Point2 & center, const Vector2 & halfExtent) :
    min(center - halfExtent),
    max(center + halfExtent)
{
}

//=============================================================================
TArray<Point2> Aabb2::GetPoints() const
{
    TArray<Point2> out;
    out.Reserve(4);

    out.Add(min);
    out.Add(Point2(min.x, max.y));
    out.Add(max);
    out.Add(Point2(max.x, min.y));

    return out;
}

//=============================================================================
void MostSeparatedPointsOnAabb (uint & min, uint & max, const TArray<Point2> & points)
{

    // first find the index of the most extreme points along principal axes
    uint minX = 0;
    uint maxX = 0;
    uint minY = 0;
    uint maxY = 0;

    for (uint i = 1; i < points.Count(); ++i)
    {
        const Point2 & p = points[i];
        if (p.x < points[minX].x) minX = i;
        if (p.x > points[maxX].x) maxX = i;
        if (p.y < points[minY].y) minY = i;
        if (p.y > points[maxY].y) maxY = i;
    }

    // Compute the squared distances for the thre pairs of points
    const float32 distSqX = DistanceSq(points[maxX], points[minX]);
    const float32 distSqY = DistanceSq(points[maxY], points[minY]);

    // Pick the pair (min, max) of most distant points
    min = minX;
    max = maxX;

    if (distSqY > distSqX)
    {
        min = minY;
        max = maxY;
    }
}



//=============================================================================
//
// Aabb3
//
//=============================================================================
const Aabb3 Aabb3::Null(Point3::One, Point3::Zero);
const Aabb3 Aabb3::Infinity(-Point3::Infinity, Point3::Infinity);

//=============================================================================
Aabb3::Aabb3()
{
}

//=============================================================================
Aabb3::Aabb3(const Point3 & min, const Point3 & max) :
    min(min),
    max(max)
{
}

//=============================================================================
Aabb3::Aabb3(const Point3 & center, const Vector3 & halfExtent) :
    min(center - halfExtent),
    max(center + halfExtent)
{
}

//=============================================================================
void MostSeparatedPointsOnAabb (uint & min, uint & max, const TArray<Point3> & points)
{
    // first find the index of the most extreme points along principal axes
    uint minX = 0;
    uint maxX = 0;
    uint minY = 0;
    uint maxY = 0;
    uint minZ = 0;
    uint maxZ = 0;

    for (uint i = 1; i < points.Count(); ++i)
    {
        const Point3 & p = points[i];
        if (p.x < points[minX].x) minX = i;
        if (p.x > points[maxX].x) maxX = i;
        if (p.y < points[minY].y) minY = i;
        if (p.y > points[maxY].y) maxY = i;
        if (p.z < points[minZ].z) minZ = i;
        if (p.z > points[maxZ].z) maxZ = i;
    }

    // Compute the squared distances for the thre pairs of points
    const float32 distSqX = DistanceSq(points[maxX], points[minX]);
    const float32 distSqY = DistanceSq(points[maxY], points[minY]);
    const float32 distSqZ = DistanceSq(points[maxZ], points[minZ]);

    // Pick the pair (min, max) of most distant points
    min = minX;
    max = maxX;

    if (distSqY > distSqX && distSqY > distSqZ)
    {
        min = minY;
        max = maxY;
    }
    else if (distSqZ > distSqX && distSqZ > distSqY)
    {
        min = minZ;
        max = maxZ; 
    }
}
