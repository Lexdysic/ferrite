
#include <Windows.h>

#include "Ferrite.h"
#include "Services\CommandLine\CommandLine.h"


using namespace Json;

namespace CommandLine
{

//*****************************************************************************
//
// CManager
//
//*****************************************************************************

class CManager : public IManager
{
public:

    CManager ();
    ~CManager ();

public: // IManager

    void Initialize () override;

    void Register (const CString & name, const Json::BoolType   & defValue) override;
    void Register (const CString & name, const Json::NumberType & defValue) override;
    void Register (const CString & name, const Json::StringType & defValue) override;
    void Register (const CString & name, const Json::ArrayType  & defValue) override;
    void Register (const CString & name, const Json::ObjectType & defValue) override;

    bool            GetBool (const CString & name) override;
    sint            GetInt (const CString & name) override;
    float32         GetFloat (const CString & name) override;
    const CString & GetString (const CString & name) override;

private:

    void Register (const CString & name, const Json::CValue & defValue);
    
    template <typename T>
    const T & Get (const CString & name);

    TDictionary<CString, CValue>    m_registered;
    CValue                          m_data;
};

//=============================================================================
CManager s_manager;

//=============================================================================
CManager::CManager ()
{
}

//=============================================================================
CManager::~CManager ()
{
}

//=============================================================================
void CManager::Initialize ()
{
    const CStringUtf16 commandUtf16 = CStringUtf16::FromData(::GetCommandLineW());

    CStringBuilder builder;
    builder += '{';
    builder += commandUtf16;
    builder += '}';

    const CString command = builder;

    CDocument doc;
    doc.Parse(command);

    ASSERT(doc.IsValid());

    m_data = doc.GetValue();
}

//=============================================================================
void CManager::Register (const CString & name, const Json::BoolType & defValue)
{
    Register(name, defValue);
}

//=============================================================================
void CManager::Register (const CString & name, const Json::NumberType & defValue)
{
    Register(name, defValue);
}

//=============================================================================
void CManager::Register (const CString & name, const Json::StringType & defValue)
{
    Register(name, defValue);
}

//=============================================================================
void CManager::Register (const CString & name, const Json::ArrayType & defValue)
{
    Register(name, defValue);
}

//=============================================================================
void CManager::Register (const CString & name, const Json::ObjectType & defValue)
{
    Register(name, defValue);
}

//=============================================================================
void CManager::Register (const CString & name, const Json::CValue & defValue)
{
    ASSERT(!m_registered.Contains(name));
    m_registered.Set(name, std::move(defValue));
}

//=============================================================================
template <typename T>
const T & CManager::Get (const CString & name)
{
    const CValue & value = m_data[name];
    const T * b = value.As<T>();
    if (b)
        return *b;

    const CValue * defValue = m_registered.Find(name);
    ASSERT(defValue);
    return *defValue->As<T>();
}

//=============================================================================
bool CManager::GetBool (const CString & name)
{
    return Get<BoolType>(name);
}

//=============================================================================
sint CManager::GetInt (const CString & name)
{
    return FloatToSint(Get<NumberType>(name));
}

//=============================================================================
float32 CManager::GetFloat (const CString & name)
{
    return float32(Get<NumberType>(name));
}

//=============================================================================
const CString & CManager::GetString (const CString & name)
{
    return Get<StringType>(name);
}

} // namespace CommandLine