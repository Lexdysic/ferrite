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

//=============================================================================
Polygon2 Polygon2::Clip (const Polygon2 & subjectPoly, const Polygon2 & clipPoly)
{
    // http://en.wikipedia.org/wiki/Sutherland%E2%80%93Hodgman_algorithm

    ASSERT(clipPoly.points.Count() >= 3);
    ASSERT(subjectPoly.points.Count() >= 3);

    Polygon2 outputList = subjectPoly;

    Point2 clipB = *clipPoly.points.Top();
    for (const auto & clipA : clipPoly.points)
    {
        const Plane2 clipPlane(clipA, clipB);

        Polygon2 inputList;
        inputList.points = std::move(outputList.points);

        Point2 subjectB = *inputList.points.Top();
        for (const auto & subjectA : inputList.points)
        {
            using namespace Geometry;

            const Line2 subjectLine(subjectA, subjectB);

            IntersectInfo2 info;
            if (Intersect(info, subjectLine, clipPlane))
                outputList.points.Add(info.point);

            if (Test(subjectA, clipPlane) == TestResult::Inside)
                outputList.points.Add(subjectA);

            subjectB = subjectA;
        }

        if (outputList.points.IsEmpty())
            break;

        clipB = clipA;
    }

    return outputList;
}