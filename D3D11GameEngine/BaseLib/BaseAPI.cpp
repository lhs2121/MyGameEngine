#include "Pre.h"
#include "BaseAPI.h"
#include "EngineStaticPool.h"
#include "EngineTime.h"


void CreateEngineStaticPool(IEngineStaticPool** ppI)
{
	*ppI = new EngineStaticPool();
}

void DeleteEngineStaticPool(IEngineStaticPool* pI)
{
	EngineStaticPool* castptr = (EngineStaticPool*)pI;
	delete castptr;
}


void CreateEngineTime(ITime** ppI)
{
	*ppI = new EngineTime();
}

void DeleteEngineTime(ITime* pI)
{
	EngineTime* castptr =(EngineTime *) pI;
	delete castptr;
}
