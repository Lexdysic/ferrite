#ifdef THRDPCH_H
#   error Connot include precompiled header more than once
#endif
#define THRDPCH_H

#include <windows.h>
#include <mutex>

#define USES_ENGINE_MATH
#define USES_ENGINE_THREAD

#include "EngineDeps.h"