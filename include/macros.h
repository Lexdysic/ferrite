
namespace fe {

//*****************************************************************************
//
// FE_CONCAT
//
//*****************************************************************************

#define FE_CONCAT_(a, b) a ## b
#define FE_CONCAT(a, b) FE_CONCAT_(a, b)



//*****************************************************************************
//
// FE_UNIQUE_SYMBOL
//
//*****************************************************************************

#define FE_UNIQUE_SYMBOL_(symbol, line) FE_CONCAT(symbol, line)
#define FE_UNIQUE_SYMBOL(symbol) FE_UNIQUE_SYMBOL_(symbol, __LINE__)



//*****************************************************************************
//
// FE_INTERFACE
//
//*****************************************************************************

#ifdef FE_COMPILER_MSVC
#  define FE_INTERFACE struct __declspec(novtable)
#else
#   define FE_INTERFACE struct
#endif



//*****************************************************************************
//
// FE_PURE
//
//*****************************************************************************

#undef FE_PURE
#define FE_PURE =0


//*****************************************************************************
//
// FE_ARRAY_SIZE
//
//*****************************************************************************

namespace core::detail
{
    template <typename T, size_t N>
    char (&ArraySizeHelper (T (&arr)[N]))[N];
}
#define FE_ARRAY_SIZE(arr) (sizeof(core::detail::ArraySizeHelper(arr)))


//*****************************************************************************
//
// FE_REF - used to surpress unrefereced formal parameter
//
//*****************************************************************************

namespace core::detail
{
    template <typename... T>
    inline void Ref(const T &... ) {}
}
#define FE_REF(...) core::Ref(__VA_ARGS__)



//*****************************************************************************
//
// FE_BREAKABLE_SCOPE
//
//*****************************************************************************

#define FE_BREAKABLE_SCOPE                              \
    for (                                               \
        bool FE_UNIQUE_SYMBOL(breakable) = true;        \
        FE_UNIQUE_SYMBOL(breakable);                    \
        FE_UNIQUE_SYMBOL(breakable) = false             \
    )



//*****************************************************************************
//
// FE_CLASS_NO_COPY
//
//*****************************************************************************

#define FE_CLASS_NO_COPY(classname)                      \
    classname (const classname &) = delete;              \
    classname & operator= (const classname &) = delete   // Note: enforce syntactic semicolon by omitting it here



//*****************************************************************************
//
// FE_CLASS_CONVERSION
//
//*****************************************************************************

#define FE_CLASS_CONVERSION(classname, interfacename)                                      \
    public:                                                                             \
    static       classname * From (interfacename * x)       { return (classname *)x; }  \
    static const classname * From (const interfacename * x) { return (classname *)x; }



//*****************************************************************************
//
// FE_NO_OP
//
//*****************************************************************************

#define FE_NO_OP __noop


//*****************************************************************************
//
// FE_STRINGIZE
//
//*****************************************************************************

#define FE_STRINGIZE_(x) #x
#define FE_STRINGIZE(x) FE_STRINGIZE_(x)



//*****************************************************************************
//
// FE_AUTO_INIT_FUNC
//
//*****************************************************************************

#define FE_AUTO_INIT_FUNC(name)     \
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
// FE_AUTO_EXIT_FUNC
//
//*****************************************************************************

#define FE_AUTO_EXIT_FUNC(name)     \
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
// FE_FORCE_NON_EMPTY
//
//*****************************************************************************

#define FE_FORCE_NON_EMPTY() namespace { char FE_CONCAT(NonEmpty, __LINE__); }

} // namespace fe