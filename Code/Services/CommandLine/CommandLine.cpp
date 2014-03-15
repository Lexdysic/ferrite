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
    const wchar * commandline = ::GetCommandLineW();
    //const CString & cmd = StringUtf16ToUtf8(commandline);

}

void Register (EType type, const CString & name)
{
}

const CString & GetString (const CString & name)
{
    return CString::Null;
}


}