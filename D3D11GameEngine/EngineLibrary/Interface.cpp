#include "pch.h"
#include "Interface.h"
#include "Engine.h"

void CreateEngine(IEngine** ppEngine)
{
    *ppEngine = new Engine();
}

void DeleteEngine(IEngine* pEngine)
{
    Engine* pCast = (Engine*)pEngine;
    delete pCast;
}
 