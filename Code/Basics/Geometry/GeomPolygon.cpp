#include "GeomPch.h"

//=============================================================================
Polygon2::Polygon2 (const TArray<Point2> & points) :
    points(points)
{
}

//=============================================================================
float32 Polygon2::ComputeArea () const
{
    float totalArea = 0.0f;

    using namespace Geometry;

    EWinding groupWinding = EWinding::Invalid;

    const Point2 & a = points[0];
    for (uint i = 2; i < points.Count(); ++i)
    {
        const Point2 & c = points[i];
        const Point2 & b = points[i-1];
        
        const Triangle2 tri(a, b, c);

        const EWinding winding = tri.ComputeWiding();
        ASSERT(winding != EWinding::Invalid);
        ASSERT(groupWinding == EWinding::Invalid || winding == groupWinding); // Can only handle convex polygons

        totalArea += tri.ComputeArea();
    }

    return totalArea;
}

//=============================================================================
Point2 Polygon2::ComputeCentroid () const
{

    //X = SUM[(Xi + Xi+1) * (Xi * Yi+1 - Xi+1 * Yi)] / 6 / A
    //Y = SUM[(Yi + Yi+1) * (Xi * Yi+1 - Xi+1 * Yi)] / 6 / A

    Vector2 center = Vector2::Zero;
    float area = 0.0f;

    Point2 a = points[points.Count() - 1];
    for (const Point2 & b : points)
    {
        auto z = Cross(a, b);
        center.y += (a.x + b.x) * z;
        center.x += (a.y + b.y) * z;

        a = b;
    }

    area /= 2.0f;
    center /= 6 * area;

    return Point2::Zero;
}

//=============================================================================
void Polygon2::ComputeInfo (Point2 * centroid, float32 * area) const
{
    ASSERT(centroid);
    ASSERT(area);

    *centroid = Vector2::Zero;
    *area = 0.0f;

    if (points.Count() < 3)
        return;

    Point2 a = points[points.Count() - 1];
    for (const Point2 & b : points)
    {
        auto z = Cross(a, b);

        *area += z;
        centroid->x += (a.x + b.x) * z;
        centroid->y += (a.y + b.y) * z;

        a = b;
    }

    *area /= 2.0f;
    *centroid /= 6 * *area;
    *area = Abs(*area);
}