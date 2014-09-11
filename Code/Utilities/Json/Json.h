namespace Json
{

//=============================================================================
//
// Constants
//
//=============================================================================

enum class EType
{
    Null,
    Bool,
    Number,
    String,
    Array,
    Object
};



//=============================================================================
//
// Forwards / Typedefs
//
//=============================================================================

class CValue;
class CReader;
class CWriter;


typedef bool                            BoolType;
typedef float64                         NumberType;
typedef CString                         StringType;
typedef TArray<CValue>                  ArrayType;
typedef TDictionary<CString, CValue>    ObjectType;



//=============================================================================
//
// CValue
//
//=============================================================================

class CValue
{
public:
    CValue ();
    CValue (const CValue & rhs);
    CValue (CValue && rhs);
    CValue (nullptr_t);
    CValue (BoolType rhs);
    CValue (NumberType rhs);
    CValue (const char rhs[]);
    CValue (const StringType & rhs);
    CValue (const ArrayType & rhs);
    CValue (const ObjectType & rhs);
    CValue (StringType && rhs);
    CValue (ArrayType && rhs);
    CValue (ObjectType && rhs);
    ~CValue ();

    CValue & operator= (const CValue & rhs);
    CValue & operator= (CValue && rhs);
    CValue & operator= (nullptr_t);
    CValue & operator= (BoolType rhs);
    CValue & operator= (NumberType rhs);
    CValue & operator= (const char rhs[]);
    CValue & operator= (const StringType & rhs);
    CValue & operator= (const ArrayType & rhs);
    CValue & operator= (const ObjectType & rhs);
    CValue & operator= (StringType && rhs);
    CValue & operator= (ArrayType && rhs);
    CValue & operator= (ObjectType && rhs);
    
    // Type conversions
    inline EType GetType () const { return m_type; }

    template <typename T>
    inline T * As ();

    template <typename T>
    inline const T * As () const;

    template <typename T>
    inline bool Is () const;

    // Indexing
    CValue & operator[] (const CString & name);
    const CValue & operator[] (const CString & name) const;

    CValue & operator[] (uint index);
    const CValue & operator[] (uint index) const;

    uint Count () const;

    inline operator bool () const;

    friend bool operator== (const CValue & lhs, const CValue & rhs);
    friend bool operator!= (const CValue & lhs, const CValue & rhs);

public:

    static const CValue Null;

private:

    static const uint DATA_BYTES = 24;

    void Copy (const CValue & rhs);
    void Move (CValue && rhs);
    void Destroy ();

    EType m_type;
    byte  m_data[DATA_BYTES];

    static_assert(DATA_BYTES >= sizeof(BoolType),   "Json::CValue::m_data is not big enough");
    static_assert(DATA_BYTES >= sizeof(NumberType), "Json::CValue::m_data is not big enough");
    static_assert(DATA_BYTES >= sizeof(StringType), "Json::CValue::m_data is not big enough");
    static_assert(DATA_BYTES >= sizeof(ArrayType),  "Json::CValue::m_data is not big enough");
    static_assert(DATA_BYTES >= sizeof(ObjectType), "Json::CValue::m_data is not big enough");
};



//=============================================================================
//
// CDocument
//
//=============================================================================

class CDocument
{
public:

    CDocument ();

    void Parse (const CPath & filepath);
    void Parse (const CString & string);

    enum class ECode
    {
        Ok,
        BadFile,
        Syntax,
        Unknown,
    };

    struct Error
    {
        ECode code;
        uint  line;
        uint  column;
        const CString & message;
    };

    bool IsValid () const { return m_code == ECode::Ok; }
    Error GetError () const { return {m_code, m_line, m_column, m_message}; }
    const ObjectType & GetValue () const { return m_object; }

private:
    enum EOption
    {
        None              = 0,
        ConsumeWhitespace = (1 << 0),
        Optional          = (1 << 1),
        OptionalConsume   = ConsumeWhitespace | Optional,
    };

    bool ParseLiteral (const char literal[], Flags32 options = EOption::ConsumeWhitespace);
    void ParseWhitespace ();
    void ParseComment ();
    bool ParseNumber (NumberType * out);
    bool ParseString (StringType * out);
    bool ParseArray (ArrayType * out);
    bool ParseObject (ObjectType * out);
    bool ParseValue (CValue * out);

    bool PostError (ECode code, const char message[], ...);
    bool Backtrace (const CString::Iterator readStart);

    String::CodePoint Read ();

    ObjectType          m_object;
    CString::Iterator   m_read;
    ECode               m_code;
    uint                m_line;
    uint                m_column;
    CString             m_message;
};

} // namespace Json

#include "Json.inl"