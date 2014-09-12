
//=============================================================================
Point3 Closest (const Point3 & p, const Plane3 & plane)
{
    return p - Distance(p, plane) * plane.n;
}

//=============================================================================
Point3 Closest (const Point3 & p, const Line3 & line)
{
    float32 t = Dot(p - line.origin, line.direction) / LengthSq(line.direction);
    return line.origin + t * line.direction;
}

//=============================================================================
Point3 Closest (const Point3 & p, const Ray3 &  line)
{
    float32 t = Dot(p - line.origin, line.direction) / LengthSq(line.direction);
    if (t < 0.0f)
        t = 0.0f;
    return line.origin + t * line.direction;
}

//=============================================================================
Point3 Closest (const Point3 & p, const Segment3 & line)
{
    const Vector3 v = line.b - line.a;
    const float32 t = Clamp(Dot(p - line.a, v) / LengthSq(v), 0.0f, 1.0f);

    return line.a + t * v;
}

//=============================================================================
Point2 Closest (const Point2 & p, const Segment2 & line)
{
    const Vector2 v = line.b - line.a;
    const float32 t = Clamp(Dot(p - line.a, v) / LengthSq(v), 0.0f, 1.0f);;
    
    return line.a + t * v;
}

//=============================================================================
Point3 Closest (const Point3 & p, const Aabb3 & box)
{
    Point3 out;
    for (uint i = 0; i < 3; ++i)
        out[i] = Clamp(p[i], box.min[i], box.max[i]);

    return out;
}

//=============================================================================
Point3 Closest (const Point3 & p, const Obb3 & box)
{
    const Vector3 d = p - box.center;
    Point3 out  = box.center;
    for (uint i = 0; i < 3; ++i)
    {
        const float32 dist = Clamp(Dot(d, box.u[i]), -box.extent[i], box.extent[i]);;
        out += dist * box.u[i];
    }
    return out;
}

//=============================================================================
Point3 Closest (const Point3 & p, const Rect3 & rect)
{
    const Vector3 d = p - rect.center;
    Point3 out  = rect.center;
    for (uint i = 0; i < 2; ++i)
    {
        const float32 dist = Clamp(Dot(d, rect.u[i]), -rect.extent[i], rect.extent[i]);
        out += dist * rect.u[i];
    }
    return out;
}