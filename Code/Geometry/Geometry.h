//=================================================================================================
//
// File:    Geom.h
// Author:  Jason Jackson
// Date:    June 5, 2009
//
// Exported interface of the geometry library
//
//=================================================================================================

#ifdef GEOM_H
# error "Cannot include header more than once"
#endif
#define GEOM_H

#include "GeomTypes.h"
#include "GeomTest.h"
#include "GeomAabb.h"
#include "GeomSegment.h" // Must be before Capsule
#include "GeomCapsule.h"
#include "GeomEllipsoid.h"
#include "GeomHalfspace.h"
#include "GeomLine.h"
#include "GeomLozenge.h"
#include "GeomObb.h"
#include "GeomPlane.h"
#include "GeomRay.h"
#include "GeomRect.h"
#include "GeomSlab.h"
#include "GeomSphere.h"
#include "GeomTriangle.h"
#include "GeomCurve.h"

#include "GeomOverlap.h"
#include "GeomClosest.h"
#include "GeomDistance.h"
#include "GeomIntersect.h"

#include "GeomClosest.inl"
#include "GeomDistance.inl"
#include "GeomOverlap.inl"
#include "GeomTest.inl"
#include "GeomAabb.inl"
#include "GeomObb.inl"
#include "GeomCurve.inl"
