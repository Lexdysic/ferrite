
namespace Json
{

enum class EOption
{
    None,
    ConsumeWhitespace
};

bool ParseLiteral (const wchar ** read, const wchar literal[], EOption option = EOption::ConsumeWhitespace);
void ParseWhitespace (const wchar ** read);
bool ParseComment (const wchar ** read);
bool ParseNumber (const wchar ** read, NumberType * out);
bool ParseString (const wchar ** read, StringType * out);
bool ParseArray (const wchar ** read, ArrayType * out);
bool ParseObject (const wchar ** read, ObjectType * out);
bool ParseValue (const wchar ** read, CValue * out);

} // namespace Json