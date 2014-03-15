
namespace CommandLine
{

enum class EType
{
    Bool,
    String,
    Int,
    Float
};

void Initialize ();
void Register (EType type, const CString & name);
const CString & GetString (const CString & name);


}