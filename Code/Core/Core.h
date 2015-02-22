#ifdef CORE_H
#  error "Cannot include Core.h more than once."
#endif
#define CORE_H

#include <type_traits>
#include <cstdint>
#include <functional>   // for std::function

#include "CorePlatform.h"
#include "CorePragma.h"
#include "CoreMacros.h"
#include "CoreTypes.h"

#include "Memory\Memory.h"
#include "Debug\Debug.h"
#include "Math\Math.h"
#include "Containers\Containers.h"
#include "String\String.h"
#include "Pointer\Pointer.h"
#include "Token\Token.h"
#include "Hash\Hash.h"

#include "CoreTypes.inl"