
namespace fe {
	
// https://sourceforge.net/p/predef/wiki/Home/


//*****************************************************************************
//
// FE_ARCH_*
//
//*****************************************************************************

#define FE_ARCH_ARM 0
#define FE_ARCH_X86 0
#define FE_ARCH_X64 0
#define FE_ARCH_PPC 0

#if defined(__i386__) || defined(_M_IX86)
#	undef  FE_ARCH_X86
#	define FE_ARCH_X86 1
#elif defined(__arm__) || defined(__aarch64__) || defined(_M_ARM)
#	undef  FE_ARCH_ARM
#	define FE_ARCH_ARM 1
#elif defined(__ia64__) || defined(_M_IA64)
#	undef  FE_ARCH_X64
#	define FE_ARCH_X64 1
#elif defined(__powerpc__) || defined(_M_PPC)
#	undef  FE_ARCH_PPC
#	define FE_ARCH_PPC 1
#else
#	error FE_ARCH_ is undefined
#endif


//*****************************************************************************
//
// FE_BITS_*
//
//*****************************************************************************

#define FE_BITS_32 0
#define FE_BITS_64 0

#if defined(__aarch64__) || defined(__ia64__)
#   undef  FE_BITS_64
#   define FE_BITS_64 1
#else
#   undef  FE_BITS_32
#   define FE_BITS_32 1
#endif


//*****************************************************************************
//
// FE_ENDIAN_*
//
//*****************************************************************************

#define FE_ENDIAN_BIG    0
#define FE_ENDIAN_LITTLE 0


//*****************************************************************************
//
// FE_OS_*
//
//*****************************************************************************

#define FE_OS_WINDOWS 0
#define FE_OS_LINUX   0
#define FE_OS_ANDROID 0
#define FE_OS_MACOS   0

#if defined(_WIN32)
#	undef  FE_OS_WINDOWS
#	define FE_OS_WINDOWS 1
#elif define(__linux__)
#	undef  FE_OS_LINUX
#	define FE_OS_LINUX 1
#elif defined(__ANDROID__)
#	undef  FE_OS_ANDROID
#	define FE_OS_ANDROID __ANDROID_API__
#elif __APPLE__ && __MACH__
#	undef  FE_OS_MACOS
#	define FE_OS_MACOS 1
#else
#	error FE_OS_ is undefined
#endif


//*****************************************************************************
//
// FE_COMPILER_*
//
//*****************************************************************************

#define FE_COMPILER_MSVC  0
#define FE_COMPILER_GCC   0
#define FE_COMPILER_CLANG 0
#define FE_COMPILER_MINGW 0

#define FE_COMPILER_VERSION_MSVC(major, minor)  (major * 100 + minor)
#define FE_COMPILER_VERSION_GCC(major, minor)   (major * 10000 + minor * 100)
#define FE_COMPILER_VERSION_CLANG(major, minor) (major * 10000 + minor * 100)
#define FE_COMPILER_VERSION_MINGW(major, minor) (major * 10000 + minor * 100)

#if defined(_MSC_VER)
#	undef  FE_COMPILER_MSVC
#	define FE_COMPILER_MSVC _MSC_VER
#elif defined(__clang__)
#	undef  FE_COMPILER_CLANG
#	define FE_COMPILER_CLANG FE_COMPILER_CLANG_VERSION(__clang_major__, __clang_minor__)
#elif defined(__GNUC__)
#	undef  FE_COMPILER_GCC
#	define FE_COMPILER_GCC FE_COMPILER_VERSION_GCC(__GNUC__, __GNUC_MINOR__)
#elif defined(__MINGW64__)
#	undef  FE_COMPILER_MINGW
#	define FE_COMPILER_MINGW FE_COMPILER_VERSION_MINGW(__MINGW64_VERSION_MAJOR, __MINGW64_VERSION_MINOR)
#else
#	error FE_COMPILER_ is undefined
#endif



//*****************************************************************************
//
// FE_RUNTIME_*
//
//*****************************************************************************

#define FE_RUNTIME_MSVC  0
#define FE_RUNTIME_GLIBC 0



//*****************************************************************************
//
// FE_CONFIG_*
//
//*****************************************************************************

#define FE_CONFIG_DEBUG   0
#define FE_CONFIG_RELEASE 0


//*****************************************************************************
//
// FE_LANGUAGE_*
//
//*****************************************************************************

#define FE_LANGUAGE_CPP 0
#define FE_LANGUAGE_CLI 0

} // namespace fe