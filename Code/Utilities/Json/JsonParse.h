
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



//=============================================================================
using Math::IsInRange;
bool IsInSet (String::CodePoint code, const char set[]);
inline bool IsInSet (String::CodePoint ch, char set);
template <typename... Ts>
bool IsInSet (String::CodePoint ch, Ts... setRest);
bool IsHexDigit (String::CodePoint ch);
uint ConvertHexDigit (String::CodePoint ch);


//=============================================================================
// TODO: move to .inl
inline bool IsInSet (String::CodePoint ch, char set)
{
    return ch == set;
}

template <typename... Ts>
bool IsInSet (String::CodePoint ch, char set, Ts... setRest)
{
    return IsInSet(ch, set) || IsInSet(ch, setRest...);
}

} // namespace Json