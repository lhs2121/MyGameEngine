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


void CreateEngineTime(IEngineTime** ppI)
{
	*ppI = new EngineTime();
}

void DeleteEngineTime(IEngineTime* pI)
{
	EngineTime* castptr =(EngineTime *) pI;
	delete castptr;
}
