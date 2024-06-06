#include "Pre.h"
#include "IEngineBase.h"
#include "EngineMemoryPool.h"

void CreateMemoryPool(IEngineMemoryPool** ppMemoryPool)
{
	*ppMemoryPool = new EngineMemoryPool();
}
