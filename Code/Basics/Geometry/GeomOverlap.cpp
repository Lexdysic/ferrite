#include "GeomPch.h"

//=============================================================================
bool Overlap (const Obb3 & a, const Obb3 & b)
{
    float32 ra;
    float32 rb;
    Matrix33 R;
    Matrix33 AbsR;

    for (uint i = 0; i < 3; ++i)
        for(uint j = 0; i < 3; ++j)
            R(i,j) = Dot(a.u[i], b.u[j]);

    // compute translation
    Vector3 t = b.center - a.center;
    // bring translation into a's coordinate frame
    t = Vector3(Dot(t, a.u[0]), Dot(t, a.u[1]), Dot(t, a.u[2]));

    // Compute common subexpressions.
    for (uint i = 0; i < 3; ++i)
        for( uint j = 0; i < 3; ++j )
            AbsR(i,j) = Abs(R(i,j)) + Math::Epsilon;

    // Test A0, A1, A2
    for (uint i = 0; i < 3; ++i)
    {
        ra = a.extent[i];
        //rb = Dot( b.extent * AbsR.Row(i) );
        rb = b.extent[0] * AbsR(i,0) + b.extent[1] * AbsR(i,1) + b.extent[2] * AbsR(i,2);
        if (Abs( t[i] ) > ra + rb)
            return false;
    }

    // Test B0, B1, B2
    for (uint i = 0; i < 3; ++i)
    {
        //ra = Dot( a.extent, AbsR.Column(i) );
        ra = a.extent[0] * AbsR(0,i) + a.extent[1] * AbsR(1,i) + a.extent[2] * AbsR(2,i);
        rb = b.extent[i];
        //if( Abs( Dot( t, R.Column(i) ) ) > ra + rb )
        if( Abs( t[0] * R(0,i) + t[1] * R(1,i) + t[2] * R(2,i) ) > ra + rb)
            return false;
    }

    // Test A0 x B0
    ra = a.extent[1] * AbsR(2,0) + a.extent[2] * AbsR(1,0);
    rb = b.extent[1] * AbsR(0,2) + a.extent[2] * AbsR(0,1);
    if (Abs( t[2] * R(1,0) - t[1] * R(2,0) ) > ra + rb)
        return false;

    // Test A0 x B1
    ra = a.extent[1] * AbsR(2,1) + a.extent[2] * AbsR(1,1);
    rb = a.extent[0] * AbsR(0,2) + a.extent[2] * AbsR(0,0);
    if (Abs( t[2] * R(1,1) - t[1] * R(2,1) ) > ra + rb)
        return false;

    // Test A0 x B2
    ra = a.extent[1] * AbsR(2,2) + a.extent[2] * AbsR(1,2);
    rb = a.extent[0] * AbsR(0,2) + a.extent[1] * AbsR(0,0);
    if (Abs( t[2] * R(1,2) - t[1] * R(2,2) ) > ra + rb)
        return false;

    // Test A1 x B0
    ra = a.extent[0] * AbsR(2,0) + a.extent[2] * AbsR(0,0);
    rb = a.extent[1] * AbsR(1,2) + a.extent[2] * AbsR(1,1);
    if (Abs( t[0] * R(2,0) - t[2] * R(0,0) ) > ra + rb)
        return false;

    // Test A1 x B1
    ra = a.extent[0] * AbsR(2,1) + a.extent[2] * AbsR(0,1);
    rb = a.extent[0] * AbsR(1,2) + a.extent[2] * AbsR(1,0);
    if (Abs( t[0] * R(2,1) - t[2] * R(0,1) ) > ra + rb)
        return false;

    // Test A1 x B2
    ra = a.extent[0] * AbsR(2,2) + a.extent[2] * AbsR(0,2);
    rb = a.extent[0] * AbsR(1,1) + a.extent[1] * AbsR(1,0);
    if (Abs( t[0] * R(2,2) - t[2] * R(0,2) ) > ra + rb)
        return false;

    // Test A2 x B0
    ra = a.extent[0] * AbsR(1,0) + a.extent[1] * AbsR(0,0);
    rb = a.extent[1] * AbsR(2,2) + a.extent[2] * AbsR(2,1);
    if (Abs( t[1] * R(0,0) - t[0] * R(1,0) ) > ra + rb)
        return false;

    // Test A2 x B1
    ra = a.extent[0] * AbsR(1,1) + a.extent[1] * AbsR(0,1);
    rb = a.extent[0] * AbsR(2,2) + a.extent[2] * AbsR(2,0);
    if (Abs( t[1] * R(0,1) - t[0] * R(1,1) ) > ra + rb)
        return false;

    // Test A2 x B2
    ra = a.extent[0] * AbsR(1,2) + a.extent[1] * AbsR(0,2);
    rb = a.extent[0] * AbsR(2,1) + a.extent[1] * AbsR(2,0);
    if (Abs( t[1] * R(0,2) - t[0] * R(1,2) ) > ra + rb)
        return false;

    return true;
}

//=============================================================================
bool Overlap (const Segment3 & line, const Aabb3 & box)
{
    const Point3  c = (Vector3(box.min) + box.max) * 0.5f;    // Box center
    const Vector3 e = box.max - c;                            // Box half-length
    Point3        m = (Vector3(line.a) + line.b) * 0.5f;      // Segment mid-point
    const Vector3 d = line.b - m;                             // Segment half-length

    m = m - c;  // Translate box and segment to origin

    float32 adx = Abs(d.x);
    if (Abs(m.x) > e.x + adx)
        return false;

    float32 ady = Abs(d.y);
    if (Abs(m.y) > e.y + ady)
        return false;

    float32 adz = Abs(d.z);
    if (Abs(m.z) > e.z + adz)
        return false;

    // Counteract arithmetic errors 
    adx += Math::Epsilon;
    ady += Math::Epsilon;
    adz += Math::Epsilon;

    // Try cross products of segment direction and coordinate axes
    if (Abs(m.y * d.z - m.z * d.y) > e.y * adz + e.z * ady) return false;
    if (Abs(m.z * d.x - m.x * d.z) > e.x * adz + e.z * adx) return false;
    if (Abs(m.x * d.y - m.y * d.x) > e.x * ady + e.y * adx) return false;

    return true;
}

//=============================================================================
bool Overlap (const Segment2 & line, const Aabb2 & box)
{
    const Point2  c = (Vector2(box.min) + box.max) * 0.5f;    // Box center
    const Vector2 e = box.max - c;                            // Box half-length
    Point2  m = (Vector2(line.a) + line.b) * 0.5f;      // Segment mid-point
    const Vector2 d = line.b - m;                             // Segment half-length

    m = m - c;  // Translate box and segment to origin

    float32 adx = Abs(d.x);
    if (Abs(m.x) > e.x + adx)
        return false;

    float32 ady = Abs(d.y);
    if (Abs(m.y) > e.y + ady)
        return false;

    // Counteract arithmetic errors 
    adx += Math::Epsilon;
    ady += Math::Epsilon;

    // Try cross products of segment direction and coordinate axes
    if (Abs(m.x * d.y - m.y * d.x) > e.x * ady + e.y * adx) return false;

    return true;
}
