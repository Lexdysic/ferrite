
//=============================================================================
//
// CURRENT_FUNCTION
//
//=============================================================================

#ifdef COMPILER_MSVC
#   define DEBUG_CURRENT_FUNCTION WIDEN(__FUNCTION__)
#else
#   error "Compiler does not support function naming
#endif


//=============================================================================
//
// ASSERT
//
//=============================================================================

#ifdef BUILD_DEBUG
#   define DEBUG_ASSERTS_ENABLED
#endif

struct DebugAssertContext
{
    bool stopChecking;
    uint count;
};

#ifdef DEBUG_ASSERTS_ENABLED
#   define ASSERT(cond)                             \
        if (!(cond))                                \
        {                                           \
            static DebugAssertContext s_context;    \
            DebugAssertion(                         \
                __WFILE__,                          \
                __LINE__,                           \
                DEBUG_CURRENT_FUNCTION,             \
                WIDEN(STRINGIZE(cond)),             \
                &s_context,                         \
                L""                                 \
            );                                      \
        }

#   define ASSERT_MSG(cond, msg, ...)               \
        if (!(cond))                                \
        {                                           \
            static DebugAssertContext s_context;    \
            DebugAssertion(                         \
                __WFILE__,                          \
                __LINE__,                           \
                DEBUG_CURRENT_FUNCTION,             \
                WIDEN(STRINGIZE(cond)),             \
                &s_context,                         \
                msg,                                \
                __VA_ARGS__                         \
            );                                      \
        }
#else
#   define ASSERT(cond) NO_OP
#   define ASSERT_MSG(cond, msg, ...) NO_OP
#endif

void DebugAssertion (
    const wchar          file[],
    uint                 line,
    const wchar          func[],
    const wchar          cond[],
    DebugAssertContext * context,
    const wchar          msg[],
    ...
);



//=============================================================================
//
// FATAL_EXIT
//
//=============================================================================

#define FATAL_EXIT(msg, ...)                \
    DebugFatalExit(                         \
        __WFILE__,                          \
        __LINE__,                           \
        DEBUG_CURRENT_FUNCTION,             \
        msg,                                \
        __VA_ARGS__                         \
    );                                      \

NO_RETURN
void DebugFatalExit (
    const wchar          file[],
    uint                 line,
    const wchar          func[],
    const wchar          msg[],
    ...
);


//=============================================================================
//
// Debug Helpers
//
//=============================================================================

bool DebugIsDebuggerAttached ();
void DebugBreakOnAllocation (uint allocation);
void DebugBreakInDebuggerElseExit ();



//=============================================================================
//
// DebugMsg
//
//=============================================================================

#ifdef BUILD_DEBUG
#   define DEBUG_MSG_ENABLED
#endif

#ifdef DEBUG_MSG_ENABLED

void DebugMsg (const char msg[], ...);
void DebugMsg (const wchar msg[], ...);
void DebugMsgV (const char msg[], va_list args);
void DebugMsgV (const wchar msg[], va_list args);

#else

inline void DebugMsg (...) {}
inline void DebugMsgV (...) {}

#endif // DEBUG_MSG_ENABLED





//=============================================================================
//
// DebugValue
//
//=============================================================================

void DebugValue (const wchar name[], float value);
void DebugValue (const wchar name[], sint value);
void DebugValue (const wchar name[], uint value);

void DebugValueGetString (wchar name[], uint len);
void DebugValueClear ();