#ifdef DEPS_H
#  error "Cannot include header more than once."
#endif
#define DEPS_H



//=============================================================================
//
// Everything gets these
//
//=============================================================================

#define USES_ENGINE_CORE
#define USES_ENGINE_MATH
#define USES_ENGINE_CONTAINERS
#define USES_ENGINE_STRING



//=============================================================================
//
// Dependencies
//
//=============================================================================

#ifdef USES_ENGINE_USER_INTERFACE
#   define USES_ENGINE_INPUT
#endif

#ifdef USES_ENGINE_GRAPHICS
#   define USES_ENGINE_ENTITY
#   define USES_ENGINE_COLOR
#   define USES_ENGINE_GEOMETRY
#endif

#ifdef USES_ENGINE_GEOMETRY
#endif

#ifdef USES_ENGINE_PHYSICS
#   define USES_ENGINE_ENTITY
#   define USES_ENGINE_GEOMETRY
#   define USES_ENGINE_TIME
#endif

#ifdef USES_ENGINE_SYSTEM
//#   define USES_ENGINE_THREAD
#   define USES_ENGINE_UTILITY_NOTIFIER
#   define USES_ENGINE_INPUT
#endif

#ifdef USES_ENGINE_THREAD
#endif

#ifdef USES_ENGINE_PATHING
#   define USES_ENGINE_UTILITY_NOTIFIER
#endif

#ifdef USES_ENGINE_INPUT
#   define USES_ENGINE_UTILITY_NOTIFIER
#   define USES_ENGINE_ENTITY
#endif

#ifdef USES_ENGINE_ENTITY
#   define USES_ENGINE_TOKEN
#   define USES_ENGINE_UTILITY_IDMANAGER
#   define USES_ENGINE_UTILITY_NOTIFIER
#endif

#ifdef USES_ENGINE_NET
#   define USES_ENGINE_TIME
#endif

#ifdef USES_ENGINE_MATH
#   define USES_ENGINE_META
#endif



//=============================================================================
//
// Include the headers
//
//=============================================================================

// CORE

#ifdef USES_ENGINE_CORE
#   include "Core\Core.h"
#   include "Core\Memory\Memory.h"
#   include "Debug\Debug.h"
#endif

#ifdef USES_ENGINE_MATH
#   include "Math\Math.h"
#endif

#ifdef USES_ENGINE_CONTAINERS
#   include "Containers\Containers.h"
#endif

#ifdef USES_ENGINE_CORE
#   include "Core\Pointer\Pointer.h"
#endif

#ifdef USES_ENGINE_STRING
#   include "String\String.h"
#endif

#ifdef USES_ENGINE_TOKEN
#   include "Token\Token.h"
#endif


// SERVICES

#ifdef USES_ENGINE_SERVICES_JSON
#   include "Services\Json\Json.h"
#endif

#ifdef USES_ENGINE_SERVICES_COMMAND_LINE
#   include "Services\CommandLine\CommandLine.h"
#endif




// UTILITIES

#ifdef USES_ENGINE_UTILITY_NOTIFIER
#   include "Utilities\Notifier\Notifier.h"
#endif

#ifdef USES_ENGINE_UTILITY_IDMANAGER
#   include "Utilities\IdManager\IdManager.h"
#endif

#ifdef USES_ENGINE_UTILITY_ALLOCATOR
#   include "Utilities\Allocator\Allocator.h"
#endif



// ...

#ifdef USES_ENGINE_GEOMETRY
#   include "Geometry\Geometry.h"
#endif

#ifdef USES_ENGINE_THREAD
#   include "Thread\Thread.h"
#endif

#ifdef USES_ENGINE_SYSTEM
#   include "System\System.h"
#endif

#ifdef USES_ENGINE_TIME
#   include "Time\Time.h"
#endif

#ifdef USES_ENGINE_COLOR
#   include "Color\Color.h"
#endif

#ifdef USES_ENGINE_META
#   include "Meta\Meta.h"
#endif

#ifdef USES_ENGINE_FILE
#   include "File\File.h"
#endif

// SYSTEMS

#ifdef USES_ENGINE_ENTITY
#   include "Entity\Entity.h"
#endif

#ifdef USES_ENGINE_PHYSICS
#   include "Physics\Physics.h"
#endif

#ifdef USES_ENGINE_GRAPHICS
#   include "Graphics\Graphics.h"
#endif

#ifdef USES_ENGINE_INPUT
#   include "Input\Input.h"
#endif

#ifdef USES_ENGINE_USER_INTERFACE
#   include "UserInterface\UserInterface.h"
#endif

#ifdef USES_ENGINE_PATHING
#   include "Pathing\Pathing.h"
#endif

#ifdef USES_ENGINE_NET
#   include "Net\Net.h"
#endif


FORCE_NON_EMPTY();