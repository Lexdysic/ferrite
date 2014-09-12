#ifdef GEOMINTERESECT_H
#  error "Cannot include header more than once."
#endif
#define GEOMINTERSECT_H

//*****************************************************************************
//
// IntersectInfo
//
//*****************************************************************************

template <typename P, typename V>
struct IntersectInfo
{
    float32 time;
    P       point;
    V       normal;
};

typedef IntersectInfo<Point2, Vector2> IntersectInfo2;
typedef IntersectInfo<Point3, Vector3> IntersectInfo3;



//*****************************************************************************
// 
// Detailed intersection testing
//
//*****************************************************************************

bool Intersect (IntersectInfo2 & out, const Line2 & l,                           const Plane2 & b);
bool Intersect (IntersectInfo2 & out, const Sphere2 & s, const Vector2 & v,      const Plane2 & p);
bool Intersect (IntersectInfo2 & out, const Sphere2 & s0, const Vector2 & v0,    const Sphere2 & s1, const Vector2 & v1);
bool Intersect (IntersectInfo2 & out, const Ray2 & r,                            const Sphere2 & s);

bool Intersect (IntersectInfo3 & out, const Sphere3 & s, const Vector3 & v,      const Plane3 & p);
bool Intersect (IntersectInfo3 & out, const Aabb3 & b, const Vector3 & v,        const Plane3 & p);
bool Intersect (IntersectInfo3 & out, const Obb3 & b, const Vector3 & v,         const Plane3 & p);
bool Intersect (IntersectInfo3 & out, const Sphere3 & s0, const Vector3 & v0,    const Sphere3 & s1);
bool Intersect (IntersectInfo3 & out, const Sphere3 & s0, const Vector3 & v0,    const Sphere3 & s1, const Vector3 & v1);
bool Intersect (IntersectInfo3 & out, const Ray3 & r,                            const Sphere3 & s);
bool Intersect (IntersectInfo3 & out, const Ray3 & r,                            const Plane3 & p);
bool Intersect (IntersectInfo3 & out, const Ray3 & r,                            const Aabb3 & b);



//*****************************************************************************
//
// Simplified boolean intersection testing
//
//*****************************************************************************

bool Intersect (const Sphere3 & s, const Vector3 & v,    const Plane3 & p);
bool Intersect (const Aabb3 & b, const Vector3 & v,      const Plane3 & p);
bool Intersect (const Obb3 & b, const Vector3 & v,       const Plane3 & p);
bool Intersect (const Sphere3 & s0, const Vector3 & v0,  const Sphere3 & s1);
bool Intersect (const Sphere3 & s0, const Vector3 & v0,  const Sphere3 & s1, const Vector3 & v1);
bool Intersect (const Ray3 & ray,                        const Sphere3 & sphere);
bool Intersect (const Ray3 & ray, const Plane3 & plane);
bool Intersect (const Ray3 & ray, const Triangle3 & tri);
bool Intersect (const Ray3 & ray, const Aabb3 & aabb);
bool Intersect (const Ray3 & ray, const Obb3 & obb);
bool Intersect (const Ray3 & ray, const Halfspace3 & hs);
bool Intersect (const Ray3 & ray, const Ellipsoid3 & ellipse);