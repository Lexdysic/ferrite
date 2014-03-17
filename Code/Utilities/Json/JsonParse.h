
namespace Json
{

enum class EOption
{
    None,
    ConsumeWhitespace
};

bool ParseLiteral (const CString::Iterator * read, const char literal[], EOption option = EOption::ConsumeWhitespace);
void ParseWhitespace (const CString::Iterator* read);
bool ParseComment (const CString::Iterator * read);
bool ParseNumber (const CString::Iterator * read, NumberType * out);
bool ParseString (const CString::Iterator * read, StringType * out);
bool ParseArray (const CString::Iterator * read, ArrayType * out);
bool ParseObject (const CString::Iterator * read, ObjectType * out);
bool ParseValue (const CString::Iterator  * read, CValue * out);

} // namespace Json