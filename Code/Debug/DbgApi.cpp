
#include "DbgPch.h"



//=============================================================================
//
// Helpers
//
//=============================================================================

//=============================================================================
AUTO_INIT_FUNC(Debug)
{
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
}



//=============================================================================
//
// ASSERT
//
//=============================================================================

//=============================================================================
void DebugAssertion (
    const wchar          file[],
    uint                 line,
    const wchar          func[],
    const wchar          cond[],
    DebugAssertContext * context,
    const wchar          msg[],
    ...
) {
    context->count++;

    if (context->stopChecking)
        return;

    // Format the message
    va_list args;
    va_start(args, msg);

    wchar message[256];
    StrPrintfV(
        message,
        msg,
        args
    );

    va_end(args);


    // Format the text
    wchar text[512];
    StrPrintf(
        text,
        L"Assertion: %s\n"
        L"%s\n"
        L"\n"
        L"Location: %s(%u) : %s\n",
        cond,
        message,
        file, line, func
    );

    // Show the message
    const int code = ::MessageBoxW(NULL, text, L"Assertion Failure", MB_ABORTRETRYIGNORE | MB_ICONERROR);
    switch (code)
    {
        case IDIGNORE:
            context->stopChecking = true;
        break;

        case IDRETRY:
        break;

        case IDABORT:
            DebugBreakInDebuggerElseExit();//DebugBreak();
        break;
    }
}


//=============================================================================
NO_RETURN void DebugFatalExit (
    const wchar file[],
    uint        line,
    const wchar func[],
    const wchar msg[],
    ...
) {
    // Format the message
    va_list args;
    va_start(args, msg);

    wchar message[256];
    StrPrintfV(
        message,
        msg,
        args
    );

    va_end(args);

    // Format the text
    wchar text[512];
    StrPrintf(
        text,
        L"Fatal Error: Program must terminate\n"
        L"%s\n"
        L"\n"
        L"Location: %s(%u) : %s\n",
        message,
        file, line, func
    );

    ::MessageBoxW(NULL, text, L"Fatal Error", MB_OK | MB_ICONERROR);

    DebugBreakInDebuggerElseExit();
}


//=============================================================================
//
// Debug Helpers
//
//=============================================================================

//=============================================================================
bool DebugIsDebuggerAttached ()
{
    return IsDebuggerPresent() > 0;
}

//=============================================================================
void DebugBreakOnAllocation (uint allocation)
{
    _CrtSetBreakAlloc(allocation);
}

//=============================================================================
void DebugBreakInDebuggerElseExit ()
{
#ifdef COMPILER_MSVC
    __try
    {
        __debugbreak();
    } __except(EXCEPTION_EXECUTE_HANDLER) {
        exit(1);
    }
#else
    exit(1);
#endif // COMPILER_MSVC
}


//=============================================================================
//
// DebugMsg
//
//=============================================================================

#ifdef DEBUG_MSG_ENABLED

//=============================================================================
void DebugOutput (const char msg[])
{
#ifdef PLATFORM_WINDOWS
    OutputDebugStringA(msg);
#else
#   error "Platform not supported"
#endif
}

//=============================================================================
void DebugOutput (const wchar msg[])
{
#ifdef PLATFORM_WINDOWS
    OutputDebugStringW(msg);
#else
#   error "Platform not supported"
#endif
}

//=============================================================================
void DebugMsg(const char msg[], ...)
{
    va_list args;
    va_start(args, msg);

    DebugMsgV(msg, args);

    va_end(args);
}

//=============================================================================
void DebugMsg(const wchar msg[], ...)
{
    va_list args;
    va_start(args, msg);

    DebugMsgV(msg, args);

    va_end(args);
}

//=============================================================================
void DebugMsgV (const char msg[], va_list args)
{
    char buffer[1024]; // BUG: Should this instead figure out the space needed?
    StrPrintfV(
        buffer,
        msg,
        args
    );

    DebugOutput(buffer);
}

//=============================================================================
void DebugMsgV (const wchar msg[], va_list args)
{
    wchar buffer[1024]; // BUG: Should this instead figure out the space needed?
    StrPrintfV(
        buffer,
        msg,
        args
    );

    DebugOutput(buffer);
}

#endif // DEBUG_MSG_ENABLED



//=============================================================================
//
// DebugValue
//
//=============================================================================

//=============================================================================
struct DebugValues
{
    TDictionary<std::wstring, float>     floats;
    TDictionary<std::wstring, sint>      sints;
    TDictionary<std::wstring, uint>      uints;
};

static DebugValues s_debugValues;

//=============================================================================
void DebugValue (const wchar name[], float value)
{
    s_debugValues.floats.Set(name, value);
}

//=============================================================================
void DebugValue (const wchar name[], sint value)
{
    s_debugValues.sints.Set(name, value);
}

//=============================================================================
void DebugValue (const wchar name[], uint value)
{
    s_debugValues.uints.Set(name, value);
}

//=============================================================================
void DebugValueGetString (wchar output[], uint outputLen)
{
    uint labelWidth = 0;
    {
        for (auto pair : s_debugValues.floats)
            labelWidth = Max(labelWidth, pair.first.length());

        for (auto pair : s_debugValues.sints)
            labelWidth = Max(labelWidth, pair.first.length());

        for (auto pair : s_debugValues.uints)
            labelWidth = Max(labelWidth, pair.first.length());
    }


    std::wstringstream stream;
    {
        for (auto pair : s_debugValues.floats)
            stream << std::left << std::setw(labelWidth) << pair.first << " = " << std::fixed << std::setprecision(2) << pair.second << std::endl;

        for (auto pair : s_debugValues.sints)
            stream  << std::left << std::setw(labelWidth) << pair.first << " = " << pair.second << std::endl;

        for (auto pair : s_debugValues.uints)
            stream << std::left << std::setw(labelWidth) << pair.first << " = " << pair.second << std::endl;
    }

    const uint len = StrPrintf(
        output,
        outputLen,
        L"%s",
        stream.str().c_str()
    );

    if (len)
        output[len-1] = L'\0';
}

//=============================================================================
void DebugValueClear ()
{
    s_debugValues.floats.Clear();
    s_debugValues.sints.Clear();
    s_debugValues.uints.Clear();
}