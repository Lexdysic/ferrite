#pragma once


//*****************************************************************************
//
// null
//
//*****************************************************************************

#define null nullptr



//*****************************************************************************
//
// CONCAT
//
//*****************************************************************************

#define CONCAT_(a, b) a ## b
#define CONCAT(a, b) CONCAT_(a, b)



//*****************************************************************************
//
// UNIQUE_SYMBOL
//
//*****************************************************************************

#define UNIQUE_SYMBOL_(symbol, line) CONCAT(symbol, line)
#define UNIQUE_SYMBOL(symbol) UNIQUE_SYMBOL_(symbol, __LINE__)



//*****************************************************************************
//
// interface
//
//*****************************************************************************

#undef interface
#ifdef COMPILER_MSVC
#  define interface struct __declspec(novtable)
#else
#   define interface struct
#endif



//*****************************************************************************
//
// pure
//
//*****************************************************************************

#undef pure
#define pure =0


//*****************************************************************************
//
// array_size
//
//*****************************************************************************

namespace Core
{
    template <typename T, size_t N>
    char (&array_size_helper (T (&arr)[N]))[N];
}
#define array_size(arr) (sizeof(Core::array_size_helper(arr)))

//template <typename T>
//constexpr size_t ArraySize (const T & arr)
//{
//    static_assert(std::is_array<T>::value, "Can only be used with arrays");
//    return std::extent<T>::value;
//}
#include <stddef.h>


//*****************************************************************************
//
// offset_of
//
//*****************************************************************************

#define offset_of(field, type)                          \
    static_cast<size_t>(                                \
        reinterpret_cast<ptrdiff_t>(                    \
            &reinterpret_cast<const uint8 &>(           \
                reinterpret_cast<type *>(null)->field   \
            )                                           \
        )                                               \
    )



//*****************************************************************************
//
// struct_of
//
//*****************************************************************************

#define struct_of(field, type, instance)                                \
    reinterpret_cast<type *>(                                           \
        reinterpret_cast<uint8 *>(&instance) - offset_of(field, type)   \
    )



//*****************************************************************************
//
// ref - used to surpress unrefereced formal parameter
//
//*****************************************************************************

template <typename... T>
inline void ref(const T &... ) {}



//*****************************************************************************
//
// breakable_scope
//
//*****************************************************************************

#define breakable_scope                             \
    for (bool UNIQUE_SYMBOL(breakable) = true; UNIQUE_SYMBOL(breakable); UNIQUE_SYMBOL(breakable) = false)



//*****************************************************************************
//
// CLASS_NO_COPY
//
//*****************************************************************************

#define CLASS_NO_COPY(classname)                         \
    classname (const classname &) = delete;              \
    classname & operator= (const classname &) = delete   // Note: enforce syntactic semicolon by omitting it here



//*****************************************************************************
//
// CLASS_CONVERSION
//
//*****************************************************************************

#define CLASS_CONVERSION(classname, interfacename)                                      \
    public:                                                                             \
    static       classname * From (interfacename * x)       { return (classname *)x; }  \
    static const classname * From (const interfacename * x) { return (classname *)x; }



//*****************************************************************************
//
// NO_OP
//
//*****************************************************************************

#define NO_OP __noop



//*****************************************************************************
//
// NO_RETURN
//
//*****************************************************************************

#define NO_RETURN __declspec(noreturn)



//*****************************************************************************
//
// STRINGIZE
//
//*****************************************************************************

#define STRINGIZE_(x) #x
#define STRINGIZE(x) STRINGIZE_(x)



//*****************************************************************************
//
// WIDEN
//
//*****************************************************************************

#define WIDEN_(x) L ## x
#define WIDEN(x) WIDEN_(x)



//*****************************************************************************
//
// __WFILE__
//
//*****************************************************************************

#define __WFILE__ WIDEN(__FILE__)



//*****************************************************************************
//
// AUTO_INIT_FUNC
//
//*****************************************************************************

#define AUTO_INIT_FUNC(name)        \
    namespace                       \
    {                               \
        struct name                 \
        {                           \
            name ();                \
        };                          \
        static name s_instance;     \
    }                               \
    name::name()



//*****************************************************************************
//
// AUTO_EXIT_FUNC
//
//*****************************************************************************

#define AUTO_EXIT_FUNC(name)        \
    namespace                       \
    {                               \
        struct name                 \
        {                           \
            ~name ();               \
        };                          \
        static name s_instance;     \
    }                               \
    name::~name()



//*****************************************************************************
//
// FORCE_NON_EMPTY
//
//*****************************************************************************

#define FORCE_NON_EMPTY() namespace { char CONCAT(NonEmpty, __LINE__); }