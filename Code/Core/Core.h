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

#include <cassert>
#include <type_traits>
#include <cstdint>
#include <functional> // for std::function

#include "CorePlatform.h"
#include "CorePragma.h"
#include "CoreMacros.h"
#include "CoreTypes.h"

#include "CoreTypes.inl"


