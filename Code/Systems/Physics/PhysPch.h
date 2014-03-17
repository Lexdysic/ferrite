//=================================================================================================
//
// File:    PhysPch.h
// Author:  Jason Jackson
// Date:    June 27, 2009
//
// Precompiled header for the physics library
//
//=================================================================================================

#ifdef PHYSPCH_H
#  error "Cannot include header more than once."
#endif
#define PHYSPCH_H

#define USES_ENGINE_MATH
#define USES_ENGINE_GEOMETRY
#define USES_ENGINE_PHYSICS
#define USES_ENGINE_GRAPHICS // for debug render

#include "EngineDeps.h"

#include "PhysComponent.h"
#include "PhysContext.h"