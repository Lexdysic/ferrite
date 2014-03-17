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

class CValue;
class CReader;
class CWriter;


typedef bool                            BoolType;
typedef float64                         NumberType;
typedef CString                         StringType;
typedef TArray<CValue>                  ArrayType;
typedef TDictionary<CString, CValue>    ObjectType;



namespace Internal
{

template <typename T> struct MapObjectType             { static const EType value = EType::Null; };
template <>           struct MapObjectType<BoolType>   { static const EType value = EType::Bool; };
template <>           struct MapObjectType<NumberType> { static const EType value = EType::Number; };
template <>           struct MapObjectType<StringType> { static const EType value = EType::String; };
template <>           struct MapObjectType<ArrayType>  { static const EType value = EType::Array; };
template <>           struct MapObjectType<ObjectType> { static const EType value = EType::Object; };
}


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
    
    inline EType GetType () const { return m_type; }

    template <typename T>
    inline T * As ();

    template <typename T>
    inline const T * As () const;

    CValue & operator[] (const CString & name);
    const CValue & operator[] (const CString & name) const;

    CValue & operator[] (uint index);
    const CValue & operator[] (uint index) const;

    uint Count () const;

    //bool operator! () const { return m_type != EType::Null; }

    friend bool operator== (const CValue & lhs, const CValue & rhs);
    friend bool operator!= (const CValue & lhs, const CValue & rhs);

public:

    static const CValue Null;

private:

    static const uint DATA_BYTES = 28;

    void Copy (const CValue & rhs);
    void Move (CValue && rhs);
    void Destroy ();

    EType m_type;
    byte  m_data[DATA_BYTES];

    static_assert(DATA_BYTES >= sizeof(BoolType), "Json::CValue::m_data is not big enough");
    static_assert(DATA_BYTES >= sizeof(NumberType), "Json::CValue::m_data is not big enough");
    static_assert(DATA_BYTES >= sizeof(StringType), "Json::CValue::m_data is not big enough");
    static_assert(DATA_BYTES >= sizeof(ArrayType), "Json::CValue::m_data is not big enough");
    static_assert(DATA_BYTES >= sizeof(ObjectType), "Json::CValue::m_data is not big enough");
};


CValue Parse (const CString & string);
CValue ParseFile (const CString & filepath);



//=============================================================================
//
// CReader
//
//=============================================================================

class CReader
{
};



//=============================================================================
//
// CWriter
//
//=============================================================================

class CWriter
{
};




template <typename T>
inline T * CValue::As ()
{
    if (Internal::MapObjectType<T>::value == m_type                            )
        return (T *)m_data;
    else
        return null;
}

template <typename T>
inline const T * CValue::As () const
{
    if (Internal::MapObjectType<T>::value == m_type)
        return (T *)m_data;
    else
        return null;
}

} // namespace Json