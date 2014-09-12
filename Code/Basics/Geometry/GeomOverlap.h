#ifdef GEOMOVERLAP_H
#  error "Cannot include header more than once."
#endif
#define GEOMOVERLAP_H

inline bool Overlap (const Sphere2 & s1,        const Sphere2 & s2);
inline bool Overlap (const Sphere3 & s1,        const Sphere3 & s2);
inline bool Overlap (const Sphere3 & sphere,    const Capsule3 & capsule);
inline bool Overlap (const Sphere3 & sphere,    const Aabb3 & box);
inline bool Overlap (const Sphere3 & sphere,    const Obb3 & box);
inline bool Overlap (const Aabb3 & box1,        const Aabb3 & box2);
inline bool Overlap (const Capsule3 & cap1,     const Capsule3 & cap2);
       bool Overlap (const Obb3 & a,            const Obb3 & b);
       bool Overlap (const Segment3 & line,     const Aabb3 & box);
       bool Overlap (const Segment2 & line,     const Aabb2 & box);
inline bool Overlap (const Aabb2 & box,         const Segment2 & line);

inline bool Contains (const Aabb2 & a, const Point2 & p);
