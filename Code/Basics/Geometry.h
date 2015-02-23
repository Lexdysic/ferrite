#ifndef BASICS_GEOMETRY_H
#define BASICS_GEOMETRY_H

#include "Geometry/GeomTypes.h"
#include "Geometry/GeomTest.h"
#include "Geometry/GeomAabb.h"
#include "Geometry/GeomSegment.h" // Must be before Capsule
#include "Geometry/GeomCapsule.h"
#include "Geometry/GeomEllipsoid.h"
#include "Geometry/GeomHalfspace.h"
#include "Geometry/GeomLine.h"
#include "Geometry/GeomLozenge.h"
#include "Geometry/GeomObb.h"
#include "Geometry/GeomPlane.h"
#include "Geometry/GeomRay.h"
#include "Geometry/GeomRect.h"
#include "Geometry/GeomSlab.h"
#include "Geometry/GeomSphere.h"
#include "Geometry/GeomTriangle.h"
#include "Geometry/GeomCurve.h"
#include "Geometry/GeomPolygon.h"

#include "Geometry/GeomOverlap.h"
#include "Geometry/GeomClosest.h"
#include "Geometry/GeomDistance.h"
#include "Geometry/GeomIntersect.h"

#include "Geometry/GeomClosest.inl"
#include "Geometry/GeomDistance.inl"
#include "Geometry/GeomOverlap.inl"
#include "Geometry/GeomTest.inl"
#include "Geometry/GeomAabb.inl"
#include "Geometry/GeomObb.inl"
#include "Geometry/GeomCurve.inl"

#endif // BASICS_GEOMETRY_H