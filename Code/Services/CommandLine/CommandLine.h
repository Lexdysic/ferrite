#ifndef SERVICES_COMMANDLINE_H
#define SERVICES_COMMANDLINE_H

#include "Utilities\Json\Json.h"

namespace CommandLine
{

//*****************************************************************************
//
// IManager
//
//*****************************************************************************

interface IManager
{
    virtual void Initialize () pure;

    virtual void Register (const CString & name, const Json::BoolType & defValue) pure;
    virtual void Register (const CString & name, const Json::NumberType & defValue) pure;
    virtual void Register (const CString & name, const Json::StringType & defValue) pure;
    virtual void Register (const CString & name, const Json::ArrayType & defValue) pure;
    virtual void Register (const CString & name, const Json::ObjectType & defValue) pure;

    virtual bool            GetBool (const CString & name) pure;
    virtual sint            GetInt (const CString & name) pure;
    virtual float32         GetFloat (const CString & name) pure;
    virtual const CString & GetString (const CString & name) pure;
};

} // namespace CommandLine

#endif // SERVICES_COMMANDLINE_H