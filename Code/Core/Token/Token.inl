

//*****************************************************************************
//
// Token
//
//*****************************************************************************

//=============================================================================
Token::Token () :
    m_value(0)
{
}

//=============================================================================
Token::Token (
    char a,
    char b,
    char c,
    char d,
    char e,
    char f,
    char g,
    char h,
    char i,
    char j,
    char k,
    char l,
    uint index
) :
    m_value(
        (Eval(a) <<  0) |
        (Eval(b) <<  5) |
        (Eval(c) << 10) |
        (Eval(d) << 15) |
        (Eval(e) << 20) |
        (Eval(f) << 25) |
        (Eval(g) << 30) |
        (Eval(h) << 35) |
        (Eval(i) << 40) |
        (Eval(j) << 45) |
        (Eval(k) << 50) |
        (Eval(l) << 55) |
        (uint64(index & 0xf) << 60)
    )
{
    ASSERT(index < MAX_INDEX);
}

//=============================================================================
template <uint N>
Token::Token (const char (& str)[N], uint index) :
    m_value(0)
{
    static_assert(N <= MAX_LEN, "Token is too long");
    ASSERT(index < MAX_INDEX);

    for (uint i = 0, n = Min(N-1, MAX_LEN); i < n; ++i)
    {
        m_value |= Eval(str[i]) << (i * 5);
    }

    m_value |= uint64(index & 0xf) << 60;
}

//=============================================================================
Token::Token (const Token & token) :
    m_value(token.m_value)
{
}

//=============================================================================
bool Token::IsValid (char ch)
{
    return CharIsUpper(String::CodePoint(ch)) || CharIsLower(String::CodePoint(ch));
}

//=============================================================================
uint64 Token::Eval (char ch)
{
    return IsValid(ch) ? (uint32(CharToUpper(String::CodePoint(ch))) - 'A') : 0;
}

//=============================================================================
bool Token::IsNull () const
{
    return m_value == 0;
}
