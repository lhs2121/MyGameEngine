#include "Pre.h"
#include "EngineBaseInterface.h"
#include "EngineMemoryPool.h"

void CreateMemoryPool(IEngineMemoryPool** ppMemoryPool)
{
	*ppMemoryPool = new EngineMemoryPool();
}
