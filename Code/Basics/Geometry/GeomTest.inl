//==================================================================================================
//
// File:    GeomTest.inl
// Author:  Jason Jackson
// Date:    December 5th, 2008
//
// Tests the positiong of one object compared to a second
//
//=================================================================================================

namespace Geometry
{

    
//=============================================================================
TestResult Test (const Point2 & point, const Plane2 & plane)
{
    const float32 dist = Distance(point, plane);

    if (dist > Math::Epsilon)       return TestResult::Outside;
    else if (dist < -Math::Epsilon) return TestResult::Inside;
    else                            return TestResult::Straddle;
}

//=============================================================================
TestResult Test (const Sphere3 & s, const Plane3 & plane)
{
    const float32 dist = Distance(s.center, plane);

    if (dist > s.radius)       return TestResult::Outside;
    else if (dist < -s.radius) return TestResult::Inside;
    else                       return TestResult::Straddle;
}

//=============================================================================
TestResult Test (const Obb3 & b, const Plane3 & plane)
{
    const float32 dist = Distance(b.center, plane);
    const float32 radius = b.ProjectedRadiusAlongVector(plane.n);

    if (dist > radius)       return TestResult::Outside;
    else if (dist < -radius) return TestResult::Inside;
    else                     return TestResult::Straddle;
}

//=============================================================================
TestResult Test (const Aabb3 & b, const Plane3 & plane)
{
    const Point3  center = (Vector3(b.min) + Vector3(b.max)) * 0.5f;
    const Vector3 extent = b.max - center;

    const float radius = extent.x * Abs(plane.n.x) + extent.y * Abs(plane.n.y) + extent.z * Abs(plane.n.z);

    const float dist = Distance(center, plane);

    if (dist > radius)       return TestResult::Outside;
    else if (dist < -radius) return TestResult::Inside;
    else                     return TestResult::Straddle;
}

} // namespace Geometry