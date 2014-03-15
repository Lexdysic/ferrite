#include "JsonPch.h"

namespace Json
{
    
//=============================================================================
bool IsInSet (wchar ch, const wchar set[])
{
    return StrFind(set, ch) != null;
}

//=============================================================================
bool IsInSet (wchar ch, wchar set)
{
    return ch == set;
}

//=============================================================================
template <typename... Ts>
bool IsInSet (wchar ch, Ts... setRest)
{
    return IsInSet(ch, set0) || IsInSet(ch, setRest...);
}

//=============================================================================
bool Error (const wchar ** read, const wchar * readStart)
{
    *read = readStart;
    return false;
}


//=============================================================================
//
// Functions
//
//=============================================================================

//=============================================================================
bool ParseLiteral (const wchar ** read, const wchar literal[], EOption option)
{
    const wchar * readStart = *read;

    if (option == EOption::ConsumeWhitespace)
        ParseWhitespace(read);

    while (*literal != '\0')
    {
        if (**read != *literal)
        {
            *read = readStart;
            return false;
        }

        (*read)++;
        literal++;
    }

    if (option == EOption::ConsumeWhitespace)
        ParseWhitespace(read);

    return true;
}

//=============================================================================
void ParseWhitespace (const wchar ** read)
{
    while (**read != L'\0' && CharIsWhitespace(**read))
        (*read)++;
}

//=============================================================================
bool ParseNumber (const wchar ** read, NumberType * out)
{
    const wchar * readStart = *read;

    enum class EState
    {
        None,
        Sign,
        Integer,
        Radix,
        Fraction,
        ExpStart,
        ExpSign,
        ExpValue,
        Error,
        End
    };

    static const wchar DIGITS[] = L"0123456789";
    static const wchar SIGNS[] = L"-+";
    static const wchar EXP_START[] = L"eE";

    EState state = EState::None;
    while (true)
    {
        const wchar ch = **read;
        switch (state)
        {
            case EState::None:
            {
                if (IsInSet(ch, SIGNS))
                    state = EState::Sign;
                else if (IsInSet(ch, DIGITS))
                    state = EState::Integer;
                else
                    state = EState::Error;
            }
            break;

            case EState::Sign:
            {
                state = EState::Integer;
            }
            break;
            
            case EState::Integer:
            {
                if (IsInSet(ch, L'.'))
                    state = EState::Radix;
                else if (IsInSet(ch, EXP_START))
                    state = EState::ExpStart;
                else if (!IsInSet(ch, DIGITS))
                    state = EState::End;
            }
            break;

            case EState::Radix:
            {
                state = EState::Fraction;
            }
            break;
            
            case EState::Fraction:
            {
                if (IsInSet(ch, EXP_START))
                    state = EState::ExpStart;
                else if (!IsInSet(ch, DIGITS))
                    state = EState::End;
            }
            break;

            case EState::ExpStart:
            {
                if (IsInSet(ch, SIGNS))
                    state = EState::ExpValue;
                else if (!IsInSet(ch, DIGITS))
                    state = EState::Error;
            }
            break;

            case EState::ExpSign:
            {
                state = EState::ExpValue;
            }
            break;           
        }

        if (state == EState::Error || state == EState::End)
            break;

        (*read)++;
    }

    if (state == EState::Error)
        return Error(read, readStart);

    const int ret = swscanf(readStart, L"%lf", out);
    if (ret != 1)
        return Error(read, readStart);

    return true;
}

//=============================================================================
bool ParseString (const wchar ** read, StringType * out)
{
    const wchar * readStart = *read;

    ParseWhitespace(read);

    if (!ParseLiteral(read, L"\"", EOption::None))
        return Error(read, readStart);

    CString & str = *out;
    str.Clear();

    while (true)
    {
        const wchar ch = *(*read)++;
        switch (ch)
        {
            case L'\0':
                return Error(read, readStart);

            case L'"':
                return true;

            case L'\\':
            {
                wchar chOut;

                const wchar ch = *(*read)++;
                switch (ch)
                {
                    case L'\0':
                        return Error(read, readStart);

                    case L'b':
                        chOut = L'\b';
                    break;

                    case L'f':
                        chOut = L'\f';
                    break;

                    case L'n':
                        chOut = L'\n';
                    break;

                    case L'r':
                        chOut = L'\r';
                    break;

                    case L't':
                        chOut = L'\t';
                    break;

                    case L'u':
                        ASSERT(false);
                        // TODO: parse unicode character
                        return false;

                    default:
                        chOut = ch;
                    break;
                }

                str += chOut;    
            }
            break;

            default:
                str += ch;
            break;
        }
    }

    return true;
}

//=============================================================================
bool ParseArray (const wchar ** read, ArrayType * out)
{
    const wchar * readStart = *read;

    if (!ParseLiteral(read, L"["))
        return Error(read, readStart);

    if (ParseLiteral(read, L"]"))
        return true;

    while (true)
    {
        CValue value;
        if (!ParseValue(read, &value))
            return Error(read, readStart);
        
        out->Add(std::move(value));

        if (!ParseLiteral(read, L","))
            break;
    }

    if (!ParseLiteral(read, L"]"))
        return Error(read, readStart);

    return true;
}

//=============================================================================
bool ParseObject (const wchar ** read, ObjectType * out)
{
    const wchar * readStart = *read;

    if (!ParseLiteral(read, L"{"))
        return Error(read, readStart);

    if (ParseLiteral(read, L"}"))
        return true;

    while (true)
    {
        CString name;
        if (!ParseString(read, &name))
            return Error(read, readStart);
        
        if (!ParseLiteral(read, L":"))
            return Error(read, readStart);


        CValue value;
        if (!ParseValue(read, &value))
            return Error(read, readStart);

        out->Set(std::move(name), std::move(value));

        if (!ParseLiteral(read, L","))
            break;
        
        if (ParseLiteral(read, L"}"))
            return true;
    }

    if (!ParseLiteral(read, L"}"))
        return Error(read, readStart);

    return true;
}

//=============================================================================
bool ParseValue (const wchar ** read, CValue * out)
{
    const wchar * readStart = *read;

    // Null
    if (ParseLiteral(read, L"null"))
    {
        *out = null;
        return true;
    }

    // Bool
    if (ParseLiteral(read, L"false"))
    {
        *out = false;
        return true;
    }

    if (ParseLiteral(read, L"true"))
    {
        *out = true;
        return true;
    }

    // Number
    NumberType number;
    if (ParseNumber(read, &number))
    {
        *out = number;
        return true;
    }

    // String
    StringType string;
    if (ParseString(read, &string))
    {
        *out = std::move(string);
        return true;
    }

    // Array
    ArrayType array;
    if (ParseArray(read, &array))
    {
        *out = std::move(array);
        return true;
    }

    // Object
    ObjectType object;
    if (ParseObject(read, &object))
    {
        *out = std::move(object);
        return true;
    }

    return Error(read, readStart);
}

//=============================================================================
CValue Parse (const CString & string)
{
    const wchar * read = string.Ptr();

    ObjectType object;
    if (ParseObject(&read, &object))
        return CValue(std::move(object));

    return CValue(null);
}

//=============================================================================
CValue ParseFile (const CString & filepath)
{
    File::CTextReader reader(filepath);
    CString text = reader.ReadAll();
    return Parse(text);
}

} // namespace Json