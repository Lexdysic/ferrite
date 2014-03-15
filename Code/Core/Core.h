//=================================================================================================
//
// File:    Core.h
// Author:  Jason Jackson
// Date:    May 20, 2009
//
// Exported interface of the core library
//
//=================================================================================================

#ifdef CORE_H
#  error "Cannot include Core.h more than once."
#endif
#define CORE_H

#include <limits>
#include <cassert>
#include <type_traits>
#include <memory>
#include <cstdint>
#include <functional>

#include <algorithm> // NOTE: consider moving this

#include "CorePlatform.h"
#include "CorePragma.h"
#include "CoreMacros.h"
#include "CoreTypes.h"

#include "CoreTypes.inl"


