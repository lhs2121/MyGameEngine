#include "Pre.h"
#include "IEngineBase.h"
#include "EngineStaticPool.h"
#include "EngineDynamicPool.h"

void CreateEngineStaticPool(IEngineStaticPool** ppIEngineStaticPool)
{
	*ppIEngineStaticPool = new EngineStaticPool();
}

void DeleteEngineStaticPool(IEngineStaticPool* pIEngineStaticPool)
{
	delete dynamic_cast<EngineStaticPool*>(pIEngineStaticPool);
}

void CreateEngineDynamicPool(IEngineDynamicPool** ppIEngineDynamicPool)
{
	*ppIEngineDynamicPool = new EngineDynamicPool();
}

void DeleteEngineDynamicPool(IEngineDynamicPool* pIEngineDynamicPool)
{
	delete dynamic_cast<EngineDynamicPool*>(pIEngineDynamicPool);
}
