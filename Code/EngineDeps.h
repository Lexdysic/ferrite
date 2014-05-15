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


// Systems

#ifdef USES_ENGINE_USER_INTERFACE
#   define USES_ENGINE_INPUT
#   define USES_ENGINE_TIME
#endif

#ifdef USES_ENGINE_GRAPHICS
#   define USES_ENGINE_ENTITY
#   define USES_ENGINE_COLOR
#   define USES_ENGINE_GEOMETRY
#endif

#ifdef USES_ENGINE_PHYSICS
#   define USES_ENGINE_ENTITY
#   define USES_ENGINE_GEOMETRY
#   define USES_ENGINE_TIME
#   define USES_ENGINE_UTILITY_NOTIFIER
#endif

#ifdef USES_ENGINE_PATHING
#   define USES_ENGINE_UTILITY_NOTIFIER
#endif

#ifdef USES_ENGINE_WINDOW
#   define USES_ENGINE_UTILITY_NOTIFIER
#   define USES_ENGINE_INPUT
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
#   define USES_ENGINE_UTILITY_NOTIFIER
#   define USES_ENGINE_TIME
#endif


// Services

#ifdef USES_ENGINE_SERVICES_COMMAND_LINE
#   define USES_ENGINE_UTILITY_JSON
#endif


// Utility

#ifdef USES_ENGINE_UTILITY_JSON
#   define USES_ENGINE_PATH
#endif


// Basic

#ifdef USES_ENGINE_FILE
#   define USES_ENGINE_PATH
#endif


// Core

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
#   include "Core\Debug\Debug.h"
#endif

#ifdef USES_ENGINE_MATH
#   include "Core\Math\Math.h"
#endif

#ifdef USES_ENGINE_CONTAINERS
#   include "Core\Containers\Containers.h"
#endif

#ifdef USES_ENGINE_CORE
#   include "Core\Pointer\Pointer.h"
#endif

#ifdef USES_ENGINE_STRING
#   include "Core\String\String.h"
#endif

#ifdef USES_ENGINE_TOKEN
#   include "Core\Token\Token.h"
#endif


// BASICS

#ifdef USES_ENGINE_GEOMETRY
#   include "Basics\Geometry\Geometry.h"
#endif

#ifdef USES_ENGINE_THREAD
#   include "Basics\Thread\Thread.h"
#endif

#ifdef USES_ENGINE_TIME
#   include "Basics\Time\Time.h"
#endif

#ifdef USES_ENGINE_COLOR
#   include "Basics\Color\Color.h"
#endif

#ifdef USES_ENGINE_META
#   include "Basics\Meta\Meta.h"
#endif

#ifdef USES_ENGINE_PATH
#   include "Basics\Path\Path.h"
#endif

#ifdef USES_ENGINE_FILE
#   include "Basics\File\File.h"
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

#ifdef USES_ENGINE_UTILITY_JSON
#   include "Utilities\Json\Json.h"
#endif



// SERVICES

#ifdef USES_ENGINE_SERVICES_COMMAND_LINE
#   include "Services\CommandLine\CommandLine.h"
#endif



// SYSTEMS

#ifdef USES_ENGINE_ENTITY
#   include "Systems\Entity\Entity.h"
#endif

#ifdef USES_ENGINE_PHYSICS
#   include "Systems\Physics\Physics.h"
#endif

#ifdef USES_ENGINE_GRAPHICS
#   include "Systems\Graphics\Graphics.h"
#endif

#ifdef USES_ENGINE_INPUT
#   include "Systems\Input\Input.h"
#endif

#ifdef USES_ENGINE_USER_INTERFACE
#   include "Systems\UserInterface\UserInterface.h"
#endif

#ifdef USES_ENGINE_PATHING
#   include "Systems\Pathing\Pathing.h"
#endif

#ifdef USES_ENGINE_NET
#   include "Systems\Net\Net.h"
#endif

#ifdef USES_ENGINE_WINDOW
#   include "Systems\Window\Window.h"
#endif


FORCE_NON_EMPTY();