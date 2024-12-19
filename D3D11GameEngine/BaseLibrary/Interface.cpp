#include "pch.h"
#include "Interface.h"
#include "EngineStaticPool.h"
#include "TimeObject.h"


void CreateEngineStaticPool(IEngineStaticPool** ppI)
{
	*ppI = new EngineStaticPool();
}

void DeleteEngineStaticPool(IEngineStaticPool* pI)
{
	EngineStaticPool* castptr = (EngineStaticPool*)pI;
	delete castptr;
}

void CreateTimeObject(ITimeObject** ppTimeObject)
{
	*ppTimeObject = new CTimeObject();
}

void DeleteTimeObject(ITimeObject* pTimeObject)
{
	CTimeObject* pCast =(CTimeObject*)pTimeObject;
	delete pCast;
}
