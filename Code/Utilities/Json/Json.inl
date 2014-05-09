
namespace Json
{


//=============================================================================
//
// MapObjectType
//
//=============================================================================

namespace Internal
{
template <typename T> struct MapObjectType             { static const EType value = EType::Null; };
template <>           struct MapObjectType<BoolType>   { static const EType value = EType::Bool; };
template <>           struct MapObjectType<NumberType> { static const EType value = EType::Number; };
template <>           struct MapObjectType<StringType> { static const EType value = EType::String; };
template <>           struct MapObjectType<ArrayType>  { static const EType value = EType::Array; };
template <>           struct MapObjectType<ObjectType> { static const EType value = EType::Object; };

} //namespace Internal


//=============================================================================
//
// CValue
//
//=============================================================================

//=============================================================================
template <typename T>
inline T * CValue::As ()
{
    if (Internal::MapObjectType<T>::value == m_type)
        return (T *)m_data;
    else
        return null;
}

//=============================================================================
template <typename T>
inline const T * CValue::As () const
{
    if (Internal::MapObjectType<T>::value == m_type)
        return (T *)m_data;
    else
        return null;
}


} // namespace Json