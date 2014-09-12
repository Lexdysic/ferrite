//=============================================================================
float32 DistanceSq (const Point2 & a, const Point2 & b)
{
    return LengthSq(a - b);
}

//=============================================================================
float32 DistanceSq (const Point3 & a, const Point3 & b)
{
    return LengthSq(a - b);
}

//=============================================================================
float32 DistanceSq (const Point3 & p, const Line3 & line)
{
    const Vector3 ap = p - line.origin;
    const float32 e  = Dot(ap, line.direction);
    const float32 f  = LengthSq(line.direction);

    return LengthSq(ap) - Sq(e) / f;
}

//=============================================================================
float32 DistanceSq (const Point3 & p, const Segment3 & line)
{
    const Vector3 ab = line.b - line.a;
    const Vector3 ap = p - line.a;
    const Vector3 bp = p - line.b;

    const float32 e = Dot(ap, ab);
    if (e <= 0.0f)
        return LengthSq(ap);

    const float32 f = LengthSq(ab);
    if (e >= f)
        return LengthSq(bp);

    return LengthSq(ap) - Sq(e) / f;
}

//=============================================================================
float32 DistanceSq (const Point3 & p, const Ray3 & ray)
{
    const Vector3 ap = p - ray.origin;
    const float32 e  = Dot(ap, ray.direction);

    if (e <= 0.0f)
        return LengthSq(ap);

    const float32 f = LengthSq(ray.direction);

    return LengthSq(ap) - Sq(e) / f;
}

//=============================================================================
float32 DistanceSq (const Point3 & p, const Aabb3 & box)
{
    float32 distSq = 0.0f;
    for (uint i = 0; i < 3; ++i)
    {
        const float32 v = p[i];
        if (v < box.min[i])
            distSq += Sq(box.min[i] - v);
        else if (v > box.max[i])
            distSq += Sq(v - box.max[i]);
    }
    return distSq;
}

//=============================================================================
float32 DistanceSq (const Point3 & p, const Obb3 & box)
{
    const Vector3 v = p - box.center;
    
    float32 distSq  = 0.0f;
    for (uint i = 0; i < 3; ++i)
    {
        const float32 d = Dot(v, box.u[i]);
        
        float32 excess;
        if (d < -box.extent[i])
            excess = d + box.extent[i];
        else if (d > box.extent[i])
            excess = d - box.extent[i];

        distSq += Sq(excess);
    }

    return distSq;
}

//=============================================================================
float32 DistanceSq (const Line3 & line1, const Line3 & line2)
{
    ASSERT(false); // TODO: implement
}

//=============================================================================
float32 Distance (const Point2 & a, const Point2 & b)
{
    return Length(a - b);
}

//=============================================================================
float32 Distance (const Point3 & a, const Point3 & b)
{
    return Length(a - b);
}

//=============================================================================
float32 Distance (const Point3 & point, const Plane3 & plane)
{
    //return Dot(plane.n, point) - plane.d; if plane is known to be normalized
    return (Dot(plane.n, point) - plane.d) / LengthSq(plane.n);
}

//=============================================================================
float32 Distance (const Point2 & point, const Plane2 & plane)
{
    //return Dot(plane.n, point) - plane.d; if plane is known to be normalized
    return (Dot(plane.n, point) - plane.d) / LengthSq(plane.n);
}


