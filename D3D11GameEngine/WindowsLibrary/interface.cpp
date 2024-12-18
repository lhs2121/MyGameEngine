#include "pch.h"
#include "interface.h"
#include "WindowObject.h"

void CreateWindowObject(IWindowObject** ppWindowObject)
{
    *ppWindowObject = new CWindowObject;
}

 void DeleteWindowObject(IWindowObject* pWindowObject)
{
     delete pWindowObject;
}
