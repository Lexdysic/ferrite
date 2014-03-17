#define USES_ENGINE_SERVICES_COMMAND_LINE
#include "EngineDeps.h"
#include <Windows.h>

namespace CommandLine
{

class CManager
{
public:
    void Parse (const CString & cmd);

private:

};








CManager s_manager;


void Initialize ()
{
    const wchar * commandLine = ::GetCommandLineW();
    const CStringUtf16 utf16 = CStringUtf16::FromData(commandLine);

    const CString utf8 = utf16;
}

void Register (EType type, const CString & name)
{
}

const CString & GetString (const CString & name)
{
    return CString::Null;
}


}