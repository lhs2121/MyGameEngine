#include "Pre.h"
#include "EngineBaseInterface.h"
#include "EngineStaticMemoryPool.h"

EngineAPI void CreateEngineStaticMemoryPool(IEngineStaticMemoryPool** ppMemoryPool)
{
	*ppMemoryPool = new EngineStaticMemoryPool();
}

EngineAPI void DeleteEngineStaticMemoryPool(IEngineStaticMemoryPool* pMemoryPool)
{
	delete dynamic_cast<EngineStaticMemoryPool*>(pMemoryPool);
}
