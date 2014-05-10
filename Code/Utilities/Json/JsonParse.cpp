#include "JsonPch.h"

namespace Json
{

//=============================================================================
bool IsInSet (String::CodePoint code, const char set[])
{
    while (char ch = *set++)
    {
        if (ch == code)
            return true;
    }
    return false;
}

//=============================================================================
bool IsHexDigit (String::CodePoint ch)
{
    return IsInRange<String::CodePoint>(ch, '0', '9')
        || IsInRange<String::CodePoint>(CharToLower(ch), 'a', 'f');
}

//=============================================================================
uint ConvertHexDigit (String::CodePoint ch)
{
    ASSERT(IsHexDigit(ch));
    if (IsInRange<String::CodePoint>(ch, '0', '9'))
        return ch - '0';

    return CharToLower(ch) - 'a' + 0xa;
}

//=============================================================================
bool Error (const CString::Iterator * read, const CString::Iterator readStart)
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
bool ParseLiteral (const CString::Iterator * read, const char literal[], EOption option)
{
    const CString::Iterator readStart = *read;

    if (option == EOption::ConsumeWhitespace)
        ParseWhitespace(read);

    while (*literal != '\0')
    {
        if (**read != (String::CodePoint)*literal)
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
void ParseWhitespace (const CString::Iterator * read)
{
    while (**read != L'\0' && CharIsWhitespace(**read))
        (*read)++;
}

//=============================================================================
bool ParseComment (const CString::Iterator * read)
{
    return true;
}

//=============================================================================
bool ParseNumber (const CString::Iterator * read, NumberType * out)
{
    const CString::Iterator readStart = *read;

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

    static const char DIGITS[] = "0123456789";
    static const char SIGNS[] = "-+";
    static const char EXP_START[] = "eE";

    EState state = EState::None;
    while (true)
    {
        const String::CodePoint ch = **read;
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
                if (IsInSet(ch, '.'))
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

    // Note: it is safe to assume the utf8 we just scanned is ascii
    const int ret = sscanf((const char *)readStart.Ptr(), "%lf", out);
    if (ret != 1)
        return Error(read, readStart);

    return true;
}

//=============================================================================
bool ParseString (const CString::Iterator * read, StringType * out)
{
    const CString::Iterator readStart = *read;

    ParseWhitespace(read);

    if (!ParseLiteral(read, "\"", EOption::None))
        return Error(read, readStart);

    TArray<String::CodePoint> str;
    str.Reserve(16);

    for (bool keepgoing = true; keepgoing; )
    {
        const String::CodePoint ch = *(*read)++;
        switch (ch)
        {
            case '\0':
                return Error(read, readStart);

            case '"':
                keepgoing = false;
                break;

            case '\\':
            {
                String::CodePoint chOut;

                const String::CodePoint ch = *(*read)++;
                switch (ch)
                {
                    case '\0':
                        return Error(read, readStart);

                    case 'b':
                        chOut = '\b';
                    break;

                    case 'f':
                        chOut = '\f';
                    break;

                    case 'n':
                        chOut = '\n';
                    break;

                    case 'r':
                        chOut = '\r';
                    break;

                    case 't':
                        chOut = '\t';
                    break;

                    case 'u':
                        chOut = 0;
                        for (uint i = 0; i < 4; ++i)
                        {
                            const String::CodePoint ch = *(*read)++;
                            if (!IsHexDigit(ch))
                                return Error(read, readStart);

                            chOut = (chOut << 4) | ConvertHexDigit(ch);
                        }
                    break;

                    default:
                        chOut = ch;
                    break;
                }

                str.Add(chOut);
            }
            break;

            default:
                str.Add(ch);
            break;
        }
    }

    str.Add(0);
    *out = CString::FromData(str);

    return true;
}

//=============================================================================
bool ParseArray (const CString::Iterator * read, ArrayType * out)
{
    const CString::Iterator readStart = *read;

    if (!ParseLiteral(read, "["))
        return Error(read, readStart);

    if (ParseLiteral(read, "]"))
        return true;

    while (true)
    {
        CValue value;
        if (!ParseValue(read, &value))
            return Error(read, readStart);
        
        out->Add(std::move(value));

        if (!ParseLiteral(read, ","))
            break;
    }

    if (!ParseLiteral(read, "]"))
        return Error(read, readStart);

    return true;
}

//=============================================================================
bool ParseObject (const CString::Iterator * read, ObjectType * out)
{
    const CString::Iterator readStart = *read;

    if (!ParseLiteral(read, "{"))
        return Error(read, readStart);

    if (ParseLiteral(read, "}"))
        return true;

    while (true)
    {
        CString name;
        if (!ParseString(read, &name))
            return Error(read, readStart);
        
        if (!ParseLiteral(read, ":"))
            return Error(read, readStart);


        CValue value;
        if (!ParseValue(read, &value))
            return Error(read, readStart);

        out->Set(std::move(name), std::move(value));

        if (!ParseLiteral(read, ","))
            break;
        
        if (ParseLiteral(read, "}"))
            return true;
    }

    if (!ParseLiteral(read, "}"))
        return Error(read, readStart);

    return true;
}

//=============================================================================
bool ParseValue (const CString::Iterator * read, CValue * out)
{
    const CString::Iterator readStart = *read;

    // Null
    if (ParseLiteral(read, "null"))
    {
        *out = null;
        return true;
    }

    // Bool
    if (ParseLiteral(read, "false"))
    {
        *out = false;
        return true;
    }

    if (ParseLiteral(read, "true"))
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
    CString::Iterator read = string.begin();
    
    ObjectType object;
    if (ParseObject(&read, &object))
        return CValue(std::move(object));

    return CValue(null);
}

//=============================================================================
CValue Parse (const CPath & filepath)
{
    File::CTextReader reader(filepath);
    CString text = reader.ReadAll();
    return Parse(text);
}

} // namespace Json