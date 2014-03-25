//=================================================================================================
//
// File:    GeomDistance.cpp
// Author:  Jason Jackson
// Date:    June 5, 2009
//
// Computes the shortest distance between objects
//
//=================================================================================================

#ifdef GEOMDISTANCE_H
#  error "Cannot include header more than once."
#endif
#define GEOMDISTANCE_H

inline float32 Distance (const Point2 & a,      const Point2 &      b);
inline float32 Distance (const Point2 & point,  const Plane2 &      plane);
       float32 Distance (const Point2 & point,  const Halfspace2 &  hs);

inline float32 Distance (const Point3 & a,      const Point3 &      b);
       float32 Distance (const Point3 & point,  const Line3 &       line);
       float32 Distance (const Point3 & point,  const Segment3 &    line);
inline float32 Distance (const Point3 & point,  const Plane3 &      plane);
       float32 Distance (const Point3 & point,  const Sphere3 &     sphere);
       float32 Distance (const Point3 & point,  const Ellipsoid3 &  ellipse);
       float32 Distance (const Point3 & point,  const Aabb3 &       aabb);
       float32 Distance (const Point3 & point,  const Obb3 &        obb);
       float32 Distance (const Point3 & point,  const Halfspace3 &  hs);

inline float32 DistanceSq (const Point2 & a,        const Point2 &      b);
       float32 DistanceSq( const Point3 & point,    const Halfspace3 &  hs);

       //float32 DistanceSq (const Point3 & point,    const Plane3 &      plane);

inline float32 DistanceSq (const Point3 & a,        const Point3 &      b);
inline float32 DistanceSq (const Point3 & point,    const Line3 &       line);
inline float32 DistanceSq (const Point3 & point,    const Segment3 &    line);
inline float32 DistanceSq (const Point3 & point,    const Ray3 &        ray);
inline float32 DistanceSq (const Point3 & point,    const Aabb3 &       box);
inline float32 DistanceSq (const Point3 & point,    const Obb3 &        box);
inline float32 DistanceSq (const Line3  & line1,    const Line3 &       line2);
       float32 DistanceSq (const Point3 & point,    const Plane3 &      plane);
       float32 DistanceSq (const Point3 & point,    const Sphere3 &     sphere);
       float32 DistanceSq (const Point3 & point,    const Ellipsoid3 &  ellipse);

       float32 DistanceSq( const Point3 & point,   const Obb3 &        obb);
       float32 DistanceSq( const Point3 & point,   const Halfspace3 &  hs);
