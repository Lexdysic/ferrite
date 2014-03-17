#include "InPch.h"


//=============================================================================
//
// CInputComponent
//
//=============================================================================

CInputComponent::CInputComponent () :
    CComponent()
{

}

CInputComponent::~CInputComponent ()
{

}




//=============================================================================
//
// IPrimativeComponent
//
//=============================================================================

//=============================================================================
const ComponentType IInputComponent::TYPE('I','n','p','u','t','C','o','n','t','r','o','l');

//=============================================================================
IInputComponent * IInputComponent::Attach (IEntity * entity)
{
    CInputComponent * comp = new CInputComponent();

    //CContext::Get()->OnCreate(comp);

    entity->Attach(comp);

    return comp;
}
