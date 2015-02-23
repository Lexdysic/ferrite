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

#include "Ferrite.h"
#include "Basics/Geometry.h"
#include "Systems/Physics.h"
#include "Systems/Graphics.h"

#include "PhysComponent.h"
#include "PhysBroadphase.h"
#include "PhysContext.h"