
#include "JsonPch.h"

using String::CodePoint;

namespace Json
{

//=============================================================================
CDocument::CDocument () :
    m_line(1),
    m_column(1)
{
}

//=============================================================================
void CDocument::Parse (const CPath & filepath)
{
    File::CTextReader reader(filepath);
    if (!reader.IsOpen())
    {
        PostError(ECode::BadFile, "File was missing or unreadable");
        return;
    }

    CString text = reader.ReadAll();
    return Parse(text);
}

//=============================================================================
void CDocument::Parse (const CString & string)
{
    m_read = string.begin();

    // Do initial error checking
    ParseWhitespace();
    if (*m_read != '{')
    {
        PostError(ECode::Syntax, "Root must be object type");
        return;
    }
    
    // Reset
    m_object.Clear();
    m_code = ECode::Unknown;

    // Read the base object
    if (ParseObject(&m_object))
        m_code = ECode::Ok;
}


//=============================================================================
bool CDocument::ParseLiteral (const char literal[], Flags32 options)
{
    const CString::Iterator readStart = m_read;

    if (options.Test(EOption::ConsumeWhitespace))
        ParseWhitespace();

    while (*literal != '\0')
    {
        if (*m_read != (CodePoint)*literal)
        {
            if (options.Test(EOption::Optional))
                return Backtrace(readStart);
            else
                return PostError(ECode::Syntax, "Unexpected token found when trying to read \"%s\"", literal);
        }

        Read();
        literal++;
    }

    if (options.Test(EOption::ConsumeWhitespace))
        ParseWhitespace();

    return true;
}

//=============================================================================
void CDocument::ParseWhitespace ()
{
    while (true)
    {
        const CodePoint ch = *m_read;

        if (ch == '\0')
        {
            break;
        }
        else if (ch == ';')
        {
            ParseComment();
        }
        else if (ch == '\n')
        {
            Read();
            m_column = 1;
            m_line++;
        }
        else if (!CharIsWhitespace(ch))
        {
            return;
        }
        else
        {
            Read();
        }
    }
}

//=============================================================================
void CDocument::ParseComment ()
{
    while (Read() != '\n')
        NO_OP;
    m_line++;
}

//=============================================================================
bool CDocument::ParseNumber (NumberType * out)
{
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

    static const char DIGITS[]    = "0123456789";
    static const char SIGNS[]     = "-+";
    static const char EXP_START[] = "eE";


    const CString::Iterator readStart = m_read;

    EState state = EState::None;
    while (true)
    {
        const CodePoint ch = *m_read;
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

        Read();
    }

    if (state == EState::Error)
        return PostError(ECode::Syntax, "could not read number");

    // Note: it is safe to assume the utf8 we just scanned is ascii
    const int ret = sscanf((const char *)readStart.Ptr(), "%lf", out);
    if (ret != 1)
        return PostError(ECode::Syntax, "could not read number");

    return true;
}

//=============================================================================
bool CDocument::ParseString (StringType * out)
{
    ParseWhitespace();

    if (!ParseLiteral("\"", EOption::None))
        return false;

    TArray<CodePoint> str;
    str.Reserve(16);

    for (bool keepgoing = true; keepgoing; )
    {
        const CodePoint ch = Read();
        switch (ch)
        {
            //case '\0':
            //    return PostError(ECode::Syntax, "newline found in string");

            case '"':
                keepgoing = false;
                break;

            case '\\':
            {
                CodePoint chOut;

                const CodePoint ch = Read();
                switch (ch)
                {
                    default:  chOut = ch;   break;
                    case 'b': chOut = '\b'; break;
                    case 'f': chOut = '\f'; break;
                    case 'n': chOut = '\n'; break;
                    case 'r': chOut = '\r'; break;
                    case 't': chOut = '\t'; break;
                    case 'u':
                        chOut = 0;
                        for (uint i = 0; i < 4; ++i)
                        {
                            const CodePoint ch = Read();

                            if (!IsHexDigit(ch))
                                return PostError(ECode::Syntax, "bad character hex digit '%c'", ch);

                            chOut = (chOut << 4) | ConvertHexDigit(ch);
                        }
                    break;                    
                    case '\0':
                        return PostError(ECode::Syntax, "newline found in string"); // Bug: is this really an error?
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
bool CDocument::ParseArray (ArrayType * out)
{
    if (!ParseLiteral("["))
        return false;

    if (ParseLiteral("]", EOption::OptionalConsume))
        return true;

    while (true)
    {
        CValue value;
        if (!ParseValue(&value))
            return false;
        
        out->Add(std::move(value));

        if (!ParseLiteral(",", EOption::OptionalConsume))
            break;

        if (ParseLiteral("]", EOption::OptionalConsume))
            return true;
    }

    if (!ParseLiteral("]"))
        return false;

    return true;
}

//=============================================================================
bool CDocument::ParseObject (ObjectType * out)
{
    if (!ParseLiteral("{"))
        return false;

    if (ParseLiteral("}", EOption::OptionalConsume))
        return true;

    while (true)
    {
        CString name;
        if (!ParseString(&name))
            return false;
        
        if (!ParseLiteral(":"))
            return false;

        CValue value;
        if (!ParseValue(&value))
            return false;

        out->Set(std::move(name), std::move(value));

        if (!ParseLiteral(",", EOption::OptionalConsume))
            break;
        
        if (ParseLiteral("}", EOption::OptionalConsume))
            return true;
    }

    if (!ParseLiteral("}"))
        return false;

    return true;
}

//=============================================================================
bool CDocument::ParseValue (CValue * out)
{
    const CodePoint ch = *m_read;
    
    // Null
    if (ch == 'n')
    {
        if (ParseLiteral("null"))
        {
            *out = null;
            return true;
        }
    }
    // Bool
    else if (IsInSet(ch, 't', 'f'))
    {
        if (ParseLiteral("false"))
        {
            *out = false;
            return true;
        }

        if (ParseLiteral("true"))
        {
            *out = true;
            return true;
        }
    }
    // Number
    else if (IsInSet(ch, '-', '+') || IsInRange<CodePoint>(ch, '0', '9'))
    {
        NumberType number;
        if (ParseNumber(&number))
        {
            *out = number;
            return true;
        }
    }
    // String
    else if (ch == '"')
    {
        StringType string;
        if (ParseString(&string))
        {
            *out = std::move(string);
            return true;
        }
    }
    // Array
    else if (ch == '[')
    {
        ArrayType array;
        if (ParseArray(&array))
        {
            *out = std::move(array);
            return true;
        }
    }
    // Object
    else if (ch == '{')
    {
        ObjectType object;
        if (ParseObject(&object))
        {
            *out = std::move(object);
            return true;
        }
    }

    return false;
}

//=============================================================================
bool CDocument::PostError (ECode code, const char message[], ...)
{
    char buffer[256];
    {
        va_list args;
        va_start(args, message);
        StrPrintfV(buffer, message, args);
        va_end(args);
    }

    m_column--; // Note: we discovered the error after having read the character
    m_code    = code;
    m_message = buffer;
    return false;
}

//=============================================================================
bool CDocument::Backtrace (const CString::Iterator readStart)
{
    const uint dist = std::distance(readStart, m_read) - 1;
    ASSERT(m_column - dist > 0);

    m_column -= dist;
    m_read = readStart;
    return false;
}

//=============================================================================
String::CodePoint CDocument::Read ()
{
    m_column++;
    return *m_read++;
}

} // namespace Json