#include "Pre.h"
#include "EngineBaseInterface.h"
#include "EngineMemoryPool.h"

EngineAPI void CreateEngineMemoryPool(IEngineMemoryPool** ppMemoryPool)
{
	*ppMemoryPool = new EngineMemoryPool();
}

EngineAPI void DeleteEngineMemoryPool(IEngineMemoryPool* pMemoryPool)
{
	delete dynamic_cast<EngineMemoryPool*>(pMemoryPool);
}
