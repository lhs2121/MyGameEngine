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
	delete (EngineStaticPool*)(pI);
}

void CreateEngineTime(IEngineTime** ppI)
{
	*ppI = new EngineTime();
}

void DeleteEngineTime(IEngineTime* pI)
{
	delete (EngineTime*)(pI);
}
