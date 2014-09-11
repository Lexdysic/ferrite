

//==================================================================================================
//
// Token
//
//==================================================================================================

class Token
{
public:

    inline Token ();
    inline explicit Token (
        char a,
        char b = '\0',
        char c = '\0',
        char d = '\0',
        char e = '\0',
        char f = '\0',
        char g = '\0',
        char h = '\0',
        char i = '\0',
        char j = '\0',
        char k = '\0',
        char l = '\0',
        uint index = 0
    );
    template <uint N>
    inline explicit Token (const char (& str)[N], uint index = 0);

    inline Token (const Token & token);

    //friend bool operator<  (Token, Token);
    //friend bool operator<= (Token, Token);
    //friend bool operator>  (Token, Token);
    //friend bool operator>= (Token, Token);
    //friend bool operator== (Token, Token);
    //friend bool operator!= (Token, Token);



    inline bool IsNull () const;

public:

    static const Token Null;
    static const uint MAX_LEN = 12;
    static const uint MAX_INDEX = 16;

    static inline bool IsValid (char ch);
    static inline uint64 Eval (char ch);

private:

    SIMPLE_TYPE_DATA(uint64, m_value);
    SIMPLE_TYPE_EQUATABLE(Token);
    SIMPLE_TYPE_COMPARABLE(Token);
};


//==================================================================================================
//
// Operations
//
//==================================================================================================

//inline bool operator<  (Token lhs, Token rhs);
//inline bool operator<= (Token lhs, Token rhs);
//inline bool operator>  (Token lhs, Token rhs);
//inline bool operator>= (Token lhs, Token rhs);
//inline bool operator== (Token lhs, Token rhs);
//inline bool operator!= (Token lhs, Token rhs);

#include "Token.inl"