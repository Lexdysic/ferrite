#include "JsonPch.h"

namespace Json
{

//*****************************************************************************
//
// CValue
//
//*****************************************************************************

//=============================================================================
const CValue CValue::Null(null);

//=============================================================================
CValue::CValue () :
    m_type(EType::Null)
{
}

//=============================================================================
CValue::CValue (const CValue & rhs)
{
    Copy(rhs);
}

//=============================================================================
CValue::CValue (CValue && rhs)
{
    Move(std::forward<CValue>(rhs));
}

//=============================================================================
CValue::CValue (nullptr_t) :
    m_type(EType::Null)
{
}

//=============================================================================
CValue::CValue (BoolType rhs) :
    m_type(EType::Bool)
{
    new(m_data) BoolType(rhs);
}

//=============================================================================
CValue::CValue (NumberType rhs) :
    m_type(EType::Number)
{
    new(m_data) NumberType(rhs);
}

//=============================================================================
CValue::CValue (const char rhs[]) :
    m_type(EType::String)
{
    new(m_data) StringType(rhs);
}

//=============================================================================
CValue::CValue (const StringType & rhs) :
    m_type(EType::String)
{
    new(m_data) StringType(rhs);
}

//=============================================================================
CValue::CValue (const ArrayType & rhs) :
    m_type(EType::Array)
{
    new(m_data) ArrayType(rhs);
}

//=============================================================================
CValue::CValue (const ObjectType & rhs) :
    m_type(EType::Object)
{
    new(m_data) ObjectType(rhs);
}

//=============================================================================
CValue::CValue (StringType && rhs) :
    m_type(EType::String)
{
    new(m_data) StringType(std::forward<StringType>(rhs));
}

//=============================================================================
CValue::CValue (ArrayType && rhs) :
    m_type(EType::Array)
{
    new(m_data) ArrayType(std::forward<ArrayType>(rhs));
}

//=============================================================================
CValue::CValue (ObjectType && rhs) :
    m_type(EType::Object)
{
    new(m_data) ObjectType(std::forward<ObjectType>(rhs));
}

//=============================================================================
CValue::~CValue ()
{
    Destroy();
}

//=============================================================================
CValue & CValue::operator= (const CValue & rhs)
{
    Destroy();
    Copy(rhs);
    return *this;
}

//=============================================================================
CValue & CValue::operator= (CValue && rhs)
{
    Destroy();
    Move(std::forward<CValue>(rhs));
    return *this;
}

//=============================================================================
CValue & CValue::operator= (nullptr_t)
{
    Destroy();
    return *this;
}

//=============================================================================
CValue & CValue::operator= (BoolType rhs)
{
    Destroy();
    m_type = EType::Bool;
    new(m_data) BoolType(rhs);
    return *this;
}

//=============================================================================
CValue & CValue::operator= (NumberType rhs)
{
    Destroy();
    m_type = EType::Number;
    new(m_data) NumberType(rhs);
    return *this;
}

//=============================================================================
CValue & CValue::operator= (const char rhs[])
{
    Destroy();
    m_type = EType::String;
    new(m_data) StringType(rhs);
    return *this;
}

//=============================================================================
CValue & CValue::operator= (const StringType & rhs)
{
    Destroy();
    m_type = EType::String;
    new(m_data) StringType(rhs);
    return *this;
}

//=============================================================================
CValue & CValue::operator= (const ArrayType & rhs)
{
    Destroy();
    m_type = EType::Array;
    new(m_data) ArrayType(rhs);
    return *this;
}

//=============================================================================
CValue & CValue::operator= (const ObjectType & rhs)
{
    Destroy();
    m_type = EType::Object;
    new(m_data) ObjectType(rhs);
    return *this;
}

//=============================================================================
CValue & CValue::operator= (StringType && rhs)
{
    Destroy();
    m_type = EType::String;
    new(m_data) StringType(std::forward<StringType>(rhs));
    return *this;
}

//=============================================================================
CValue & CValue::operator= (ArrayType && rhs)
{
    Destroy();
    m_type = EType::Array;
    new(m_data) ArrayType(std::forward<ArrayType>(rhs));
    return *this;
}

//=============================================================================
CValue & CValue::operator= (ObjectType && rhs)
{
    Destroy();
    m_type = EType::Object;
    new(m_data) ObjectType(std::forward<ObjectType>(rhs));
    return *this;
}

//=============================================================================
CValue & CValue::operator[] (const CString & name)
{
    ASSERT(m_type == EType::Object);
    
    auto * obj = this->As<ObjectType>();

    if (!obj->Contains(name))
        obj->Set(name, CValue::Null);

    auto * value = obj->Find(name);
    ASSERT(value);

    return *value;
}

//=============================================================================
const CValue & CValue::operator[] (const CString & name) const
{
    if (m_type != EType::Object)
        return CValue::Null;

    const auto * value = this->As<ObjectType>()->Find(name);
    if (!value)
        return CValue::Null;

    return *value;
}
//
////=============================================================================
//CValue & CValue::operator[] (const char * const name) {
//    return (*this)[CString(name)];
//}
//
////=============================================================================
//const CValue & CValue::operator[] (const char * const name) const {
//    return (*this)[CString(name)];
//}

//=============================================================================
CValue & CValue::operator[] (uint index)
{
    ASSERT(m_type == EType::Array);

    auto & array = *this->As<ArrayType>();
    array.Resize(index + 1);

    return array[index];
}

//=============================================================================
const CValue & CValue::operator[] (uint index) const
{
    if (m_type != EType::Array)
        return CValue::Null;

    const auto * array = this->As<ArrayType>();
    if (index >= array->Count())
        return CValue::Null;

    return (*array)[index];
}

//=============================================================================
uint CValue::Count () const
{
    switch (m_type)
    {
        case EType::String: return this->As<StringType>()->Length();
        case EType::Array:  return this->As<ArrayType>()->Count();
        case EType::Object: return this->As<ObjectType>()->Count();
        default: return 0;
    }
}

//=============================================================================
void CValue::Copy (const CValue & rhs)
{
    m_type = rhs.m_type;
    switch (m_type)
    {
        case EType::Bool:   new(m_data) BoolType(*rhs.As<BoolType>()); break;
        case EType::Number: new(m_data) NumberType(*rhs.As<NumberType>()); break;
        case EType::String: new(m_data) StringType(*rhs.As<StringType>()); break;
        case EType::Array:  new(m_data) ArrayType(*rhs.As<ArrayType>());  break;
        case EType::Object: new(m_data) ObjectType(*rhs.As<ObjectType>()); break;
    }
}

//=============================================================================
void CValue::Move (CValue && rhs)
{
    m_type = rhs.m_type;
    switch (m_type)
    {
        case EType::Bool:   new(m_data) BoolType(std::forward<BoolType>(*rhs.As<BoolType>())); break;
        case EType::Number: new(m_data) NumberType(std::forward<NumberType>(*rhs.As<NumberType>())); break;
        case EType::String: new(m_data) StringType(std::forward<StringType>(*rhs.As<StringType>())); break;
        case EType::Array:  new(m_data) ArrayType(std::forward<ArrayType>(*rhs.As<ArrayType>()));  break;
        case EType::Object: new(m_data) ObjectType(std::forward<ObjectType>(*rhs.As<ObjectType>())); break;
    }
    rhs = null;
}

//=============================================================================
void CValue::Destroy ()
{
    switch (m_type)
    {
        case EType::String: this->As<StringType>()->~StringType(); break;
        case EType::Array:  this->As<ArrayType>()->~ArrayType(); break;
        case EType::Object: this->As<ObjectType>()->~ObjectType(); break;
    }
    m_type = EType::Null;
}


//=============================================================================
bool operator== (const CValue & lhs, const CValue & rhs)
{
    if (lhs.m_type != rhs.m_type)
        return false;

    switch (lhs.m_type)
    {
        case EType::Bool:   return *lhs.As<BoolType>()   == *rhs.As<BoolType>();
        case EType::Number: return *lhs.As<NumberType>() == *rhs.As<NumberType>();
        case EType::String: return *lhs.As<StringType>() == *rhs.As<StringType>();
        case EType::Array:  return *lhs.As<ArrayType>()  == *rhs.As<ArrayType>();
        case EType::Object: return *lhs.As<ObjectType>() == *rhs.As<ObjectType>();
    }

    return true;
}

//=============================================================================
bool operator!= (const CValue & lhs, const CValue & rhs)
{
    return !(lhs == rhs);
}

}