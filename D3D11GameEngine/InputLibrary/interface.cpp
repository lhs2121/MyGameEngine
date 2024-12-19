#include "pch.h"
#include "interface.h"
#include "InputObject.h"

void CreateInputObject(IInputObject** ppTimeObject)
{
	*ppTimeObject = new CInputObject();
}

void DeleteInputObject(IInputObject* pTimeObject)
{
	delete pTimeObject;
}
