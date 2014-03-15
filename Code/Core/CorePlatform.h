//=================================================================================================
//
// File:    CorePlatform.h
// Author:  Jason Jackson
// Date:    May 20, 2009
//
//=================================================================================================

#ifdef COREPLATFORM_H
#  error "Cannot include header more than once"
#endif
#define COREPLATFORM_H


//=============================================================================
//
// Config
//
//=============================================================================

//#if defined(_CONSOLE)
//#   define CONFIG_CONSOLE
//#else
//#   define CONFIG_WINDOWED
//#endif



//=============================================================================
//
// Operating System
//
//=============================================================================

#if defined(_WIN32) || defined(_WIN64)
#   define PLATFORM_WINDOWS
#elif defined(TARGET_OS_MAC)
#   define PLATFORM_MAC
#elif defined(__linux__)
#   define PLATFORM_LINUX
#else
#   error "Unknown platform"
#endif



//=============================================================================
//
// Compiler
//
//=============================================================================

#if defined(_MSC_VER)
#   define COMPILER_MSVC
#elif defined(__clang__)
#   define COMPILER_CLANG
#elif defined(__GNUC__)
#   define COMPILER_GCC
#elif defined(__INTEL_COMPILER)
#   define COMPILER_INTEL
#elif defined(__llvm__)
#   define COMPILER_LLVM
#else
#   error "Unknown Compiler"
#endif



//=============================================================================
//
// Build
//
//=============================================================================

//#if defined(_DEBUG)
//#   define BUILD_DEBUG
//#else
//#   define BUILD_RELEASE
//#endif



//=============================================================================
//
// PLATFORM_MAIN
//
//=============================================================================

#ifdef PLATFORM_WINDOWS
#   define PLATFORM_MAIN()   CALLBACK WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
#else
#   define PLATFORM_MAIN()   main ()
#endif