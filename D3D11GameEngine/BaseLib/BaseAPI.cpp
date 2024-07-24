#include "Pre.h"
#include "BaseAPI.h"
#include "EngineStaticPool.h"
#include "EngineList.h"


void CreateEngineStaticPool(IEngineStaticPool** ppIEngineStaticPool)
{
	*ppIEngineStaticPool = new EngineStaticPool();
}

void DeleteEngineStaticPool(IEngineStaticPool* pIEngineStaticPool)
{
	delete (EngineStaticPool*)(pIEngineStaticPool);
}
