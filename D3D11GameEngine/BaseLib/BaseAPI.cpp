#include "Pre.h"
#include "BaseAPI.h"
#include "EngineStaticPool.h"
#include "EngineTime.h"


void CreateEngineStaticPool(IEngineStaticPool** ppIEngineStaticPool)
{
	*ppIEngineStaticPool = new EngineStaticPool();
}

void DeleteEngineStaticPool(IEngineStaticPool* pIEngineStaticPool)
{
	delete (EngineStaticPool*)(pIEngineStaticPool);
}

void CreateEngineTime(IEngineTime** ppIEngineTime)
{
	*ppIEngineTime = new EngineTime();
}

void DeleteEngineTime(IEngineTime* pIEngineTime)
{
	delete (EngineTime*)(pIEngineTime);
}
