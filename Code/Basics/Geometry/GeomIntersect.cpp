#include "GeomPch.h"

//=============================================================================
bool Intersect (IntersectInfo2 & out, const Line2 & line, const Plane2 & plane)
{
    out.time  = (plane.d - Dot(plane.n, line.origin)) / Dot(plane.n, line.direction);
    out.point = line.origin + out.time * line.direction;

    const bool isValid = Math::IsInRange(out.time, 0.0f, 1.0f);

    return isValid;
}

//=============================================================================
bool Intersect (IntersectInfo2 & out, const Sphere2 & s, const Vector2 & v, const Plane2 & p)
{
    const float32 dist = Distance(s.center, p);

    // Sphere starts out touching the plane
    if (Abs(dist) <= s.radius)
    {
        out.time    = 0.0f;
        out.point   = s.center;
    }
    else
    {
        const float32 denom = Dot(p.n, v);

        // Is sphere moving parallel or away from the plane?
        if (denom * dist >= 0.0f)
        {
            return false;
        }
        else
        {
            const float32 r = dist > 0.0f ? s.radius : -s.radius;

            out.time  = (r - dist) / denom;
            out.point = s.center + out.time * v - r * p.n;
        }
    }

    return true;
}

//=============================================================================
bool Intersect (IntersectInfo3 & out, const Sphere3 & s, const Vector3 & v, const Plane3 & p)
{
    const float32 dist = Distance(s.center, p);

    // Sphere starts out touching the plane
    if (Abs(dist) <= s.radius)
    {
        out.time  = 0.0f;
        out.point = s.center;
    }
    else
    {
        const float32 denom = Dot(p.n, v);

        // Is sphere moving parallel or away from the plane?
        if (denom * dist >= 0.0f)
        {
            return false;
        }
        else
        {
            const float32 r = (dist > 0.0f) ? s.radius : -s.radius;

            out.time  = (r - dist) / denom;
            out.point = s.center + out.time * v - r * p.n;
        }
    }
    return true;
}

//=============================================================================
bool Intersect (const Sphere3 & s, const Vector3 & v, const Plane3 & p)
{
    const float32 distStart = Distance(s.center, p);
    const float32 distEnd   = Distance(s.center + v, p);

    // Sphere start and ends on differnt sides of the plane
    if (distStart * distEnd < 0.0f) 
        return true;

    // Sphere start or end poition is within radius from plane
    if (Abs(distStart) <= s.radius || Abs(distEnd) <= s.radius)
        return true;

    return false;
}

//=============================================================================
bool Intersect (IntersectInfo3 & out, const Aabb3 & b, const Vector3 & v, const Plane3 & p)
{
    const Vector3 extent = (b.max - b.min) * 0.5f;
    const Point3  center = b.min + extent;
    const float32 radius = Dot(extent, Abs(v));

    const float32 dist = Distance(center, p);

    // Sphere starts out touching the plane
    if (Abs(dist) <= radius)
    {
        out.time  = 0.0f;
        out.point = center;
    }
    else
    {
        const float32 denom = Dot(p.n, v);

        // Is sphere moving parallel or away from the plane?
        if (denom * dist >= 0.0f)
        {
            return false;
        }
        else
        {
            const float32 r = (dist > 0.0f) ? radius : -radius;

            out.time  = (r - dist) / denom;
            out.point = center + out.time * v - r * p.n;
        }
    }
    return true;
}

//=============================================================================
bool Intersect (const Aabb3 & b, const Vector3 & v, const Plane3 & p)
{
    const Vector3 extent = (b.max - b.min) * 0.5f;
    const Point3  center = b.min + extent;
    const float32 radius = Dot(extent, Abs(v));

    const float32 distStart = Distance(center, p);
    const float32 distEnd   = Distance(center + v, p);

    // Box start and ends on differnt sides of the plane
    if (distStart * distEnd < 0.0f) 
        return true;

    // Box start or end poition is within radius from plane
    if (Abs(distStart) <= radius || Abs(distEnd) <= radius)
        return true;

    return false;
}

//=============================================================================
bool Intersect (IntersectInfo3 & out, const Obb3 & b, const Vector3 & v, const Plane3 & p)
{
    const float32 radius = b.ProjectedRadiusAlongVector(p.n);
    const float32 dist   = Distance(b.center, p);

    // Sphere starts out touching the plane
    if (Abs(dist) <= radius)
    {
        out.time  = 0.0f;
        out.point = b.center;
    }
    else
    {
        const float32 denom = Dot(p.n, v);

        // Is sphere moving parallel or away from the plane?
        if (denom * dist >= 0.0f)
        {
            return false;
        }
        else
        {
            const float32 r = (dist > 0.0f) ? radius : -radius;

            out.time  = (r - dist) / denom;
            out.point = b.center + out.time * v - r * p.n;
        }
    }

    return true;
}

//=============================================================================
bool Intersect (const Obb3 & b, const Vector3 & v, const Plane3 & p)
{
    const float32 radius    = b.ProjectedRadiusAlongVector(p.n);
    const float32 distStart = Distance(b.center, p);
    const float32 distEnd   = Distance(b.center + v, p);

    // Box start and ends on differnt sides of the plane
    if (distStart * distEnd < 0.0f)
        return true;

    // Box start or end poition is within radius from plane
    if (Abs(distStart) <= radius || Abs(distEnd) <= radius)
        return true;

    return false;
}

//=============================================================================
bool Intersect (IntersectInfo3 & out, const Sphere3 & s0, const Vector3 & v0, const Sphere3 & s1)
{
    return Intersect(
        out,
        Ray3(s0.center, v0),
        Sphere3(s1.center, s0.r + s1.r)
    );
}

//=============================================================================
bool Intersect (const Sphere3 & s0, const Vector3 & v0, const Sphere3 & s1)
{
    return Intersect(
        Ray3(s0.center, v0),
        Sphere3(s1.center, s0.r + s1.r)
    );
}

//=============================================================================
bool Intersect (IntersectInfo2 & out, const Sphere2 & s0, const Vector2 & v0, const Sphere2 & s1, const Vector2 & v1)
{
    const Vector2 v = v0 - v1;
    const float32 vLen = Length(v);

    if (Intersect(out, Ray2(s0.center, v / vLen), Sphere2(s1.center, s0.r + s1.r)))
    {
        if (out.time <= vLen)
        {
            // sphere center at time of collision
            const Point2 p0 = s0.center + v0 * out.time;
            const Point2 p1 = s1.center + v1 * out.time;
            // TODO: compute the actual point of contact
            return true;
        }
    }
    
    return false;
}

//=============================================================================
bool Intersect (IntersectInfo3 & out, const Sphere3 & s0, const Vector3 & v0, const Sphere3 & s1, const Vector3 & v1)
{
    return Intersect(
        out,
        Ray3(s0.center, v0 - v1),
        Sphere3(s1.center, s0.r + s1.r)
    );
}

//=============================================================================
bool Intersect (const Sphere3 & s0, const Vector3 & v0, const Sphere3 & s1, const Vector3 & v1)
{
    return Intersect(
        Ray3(s0.center, v0 - v1),
        Sphere3(s1.center, s0.r + s1.r)
    );
}

//=============================================================================
bool Intersect (IntersectInfo2 & out, const Ray2 & r, const Sphere2 & s)
{
    const Vector2 m = r.origin - s.center;
    const float32 b = 2.0f * Dot(m, r.direction);
    const float32 c = LengthSq(m) - Sq(s.radius);

    // the ray starts outside of the sphere and is pointing away
    if (c > 0.0f && b > 0.0f)
        return false;

    const float32 a = LengthSq(r.direction);

    const float32 discr = Sq(b) - 4.0f * a * c;

    // ray missed the sphere?
    if (discr < 0.0f)
        return false;

    out.time = (-b - Sqrt(discr)) / (2.0f * a);

    // ray started inside sphere?
    if (out.time < 0.0f) 
        out.time = 0.0f;

    out.point = r.origin + out.time * r.direction;

    return true;
}

//=============================================================================
bool Intersect (IntersectInfo3 & out, const Ray3 & r, const Sphere3 & s)
{
#define RAY_SPHERE_HANDLE_START_INSIDE
    const Point3 &  p = r.origin;
    const Vector3 & d = r.direction;

    const Vector3 m = p - s.center;
    const float32 a = LengthSq(d);
    const float32 b = 2.0f * Dot(m, d);
    const float32 c = LengthSq(m) - Sq(s.radius);

    // the ray starts outside of the sphere and is pointing away
    const bool isOutside = c >= -0.001f;
    const bool isAway    = b >= 0.0;
    if (isOutside && isAway)
        return false;

    const float32 discr = Sq(b) - 4.0f * a * c;

    // ray missed the sphere?
    if (discr < 0.0f)
        return false;

#ifdef RAY_SPHERE_HANDLE_START_INSIDE
    //ASSERT(bOutside);
    const float32 sign = isOutside ? -1.0f : 1.0f;
    out.time = (-b + sign * Sqrt(discr)) / (2.0f * a);
#else
    out.time = (-b - Sqrt(discr)) / (2.0f * a);

    // ray started inside sphere?
    if (out.time < 0.0f)
        return false;
#endif

    out.point = r.origin + out.time * r.direction;
    out.normal = out.point - s.center;
    return true;
}

//
////=============================================================================
//bool Intersect( IntersectInfo3 & out, const Ray3 & r, const Sphere3 & s )
//{
//#define RAY_SPHERE_HANDLE_START_INSIDE
//  const Point3 & p = r.origin;
//  const Vector3 & d = r.direction;
//
//  //ASSERT(Normalized(d));
//
//  const Vector3  m = p - s.center;
//  const float32 b = Dot(m, d);
//  const float32 c = LengthSq(m) - Sq(s.radius);
//
//  // the ray starts outside of the sphere and is pointing away
//  const bool bOutside = c >= 0.001f || Equal(c, 0.001f);
//  const bool bAway    = b >= 0.0;
//  if( bOutside && bAway )
//      return false;
//
//  const float32 discr = Sq(b) - c;
//
//  // ray missed the sphere?
//  if( discr < 0.0f )
//      return false;
//
//#ifdef RAY_SPHERE_HANDLE_START_INSIDE
//  //ASSERT(bOutside);
//  const float32 sign = bOutside ? -1.0f : 1.0f;
//  out.time = -b + sign * Sqrt(discr);
//#else
//  out.time = -b - Sqrt(discr);
//
//  // ray started inside sphere?
//  if( out.time < 0.0f )
//      return false;
//#endif
//
//  out.point = r.origin + out.time * r.direction;
//  out.normal = out.point - s.center;
//  return true;
//}

//=============================================================================
bool Intersect (const Ray3 & r, const Sphere3 & s)
{
    const Vector3 m = r.origin - s.center;
    const float32 c = LengthSq(m) - Sq(s.radius);

    // Ray starts inside?
    if (c <= 0.0f)
        return true;

    const float32 b = Dot(m, r.direction);

    // ray outside and pointing away
    if (b > 0.0f)
        return false;

    const float32 a     = LengthSq(r.direction);
    const float32 discr = Sq(b) - a * c;

    // ray missed sphere
    if (discr < 0.0f)
        return false;

    return true;
}

//=============================================================================
bool Intersect (IntersectInfo3 & out, const Ray3 & r, const Plane3 & p)
{
    out.time = (p.d - Dot(p.n, r.origin)) / Dot(p.n, r.direction);
    out.point = r.origin + out.time * r.direction;

    return true;
}

//=============================================================================
bool Intersect (IntersectInfo3 & out, const Ray3 & r, const Aabb3 & b)
{
    float32 &   tmin = out.time;
    float32     tmax = std::numeric_limits<float32>::max();
    tmin = 0;

    Vector3 nmin(1e-10f, 1e-11f, 1e-12f);

    static const Vector3 s_normals[] = {
        Vector3(1.0f, 0.0f, 0.0f),
        Vector3(0.0f, 1.0f, 0.0f),
        Vector3(0.0f, 0.0f, 1.0f)
    };

    for (uint i = 0; i < 3; ++i)
    {
        // ray is parallel to slab?
        //if (Equal(r.direction[i], 0.0f))
        if (Abs(r.direction[i]) < 0.0001f)
        {
            if (r.origin[i] < b.min[i] || r.origin[i] > b.max[i])
                return false;
        }
        else
        {
            const float32 ood = 1.0f / r.direction[i];
            float32 t1 = (b.min[i] - r.origin[i]) * ood;
            float32 t2 = (b.max[i] - r.origin[i]) * ood;
            const Vector3 & n1 = s_normals[i];
            //Vector3  n2 = Vector3::Zero; n2[i] = +1.0f;

            float32 nSign = 1.0f;
            // make sure that t1 is always less than or equal to t2
            if (t1 > t2)
            {
                std::swap(t1, t2);
                nSign = -1.0f;
                //std::swap(n1, n2);
            }

            if (t1 > tmin)
            {
                tmin = t1;
                nmin = n1 * nSign;
            }

            //tmin = Max(tmin, t1);
            tmax = Min(tmax, t2);

            if (tmin > tmax)
                return false;
        }
    }

    out.point  = r.origin + tmin * r.direction;
    out.normal = nmin;

    return true;
}